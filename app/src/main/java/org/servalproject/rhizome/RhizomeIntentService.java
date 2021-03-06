/*
 * Copyright (c) 2012, The Serval Project
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the The Serval Project nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE SERVAL PROJECT BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

package org.servalproject.rhizome;

import android.app.IntentService;
import android.content.Intent;
import android.net.Uri;
import android.util.Log;

import org.servalproject.ServalBatPhoneApplication;
import org.servalproject.servaldna.ServalDCommand;
import org.servalproject.servaldna.keyring.KeyringIdentity;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.OutputStream;
import java.util.ArrayList;
import java.util.List;

/**
 * respond to incoming intents to add a file to the Rhizome repository
 */
public class RhizomeIntentService extends IntentService {

    /*
     * class level constants
     */
    private final String TAG = "RhizomeIntentService";

    public RhizomeIntentService() {
        super("RhizomeIntentService");
    }

    @Override
    protected void onHandleIntent(Intent intent) {
        try {
            // check to see if all of the parameters are available
            if (intent == null)
                throw new IllegalArgumentException(
                        "service called without an intent");

            if (!intent.getAction()
                    .equals("org.servalproject.rhizome.ADD_FILE"))
                throw new IllegalArgumentException(
                        "service called with incorrect intent action");

            String path = null;

            Uri uri = intent.getData();
            if (uri != null) {
                path = ShareFileActivity.getRealPathFromURI(this, uri);
            } else {
                path = intent.getStringExtra("path");
            }

            if (path == null)
                throw new IllegalArgumentException(
                        "service called without the path extra");

            File mPayloadFile = new File(path);
            if (!mPayloadFile.exists())
                throw new FileNotFoundException(
                        "service called with a missing file");

            File mManifestFile = null;

            String mManifest = intent.getStringExtra("manifest");
            List<String> args = new ArrayList<String>();

            if (mManifest != null) {
                // use the supplied manifest
                mManifestFile = new File(mManifest);
                if (!mManifestFile.exists())
                    throw new FileNotFoundException("manifest file not found");
            } else {
                long mVersion = intent.getLongExtra("version", -1);
                String name = intent.getStringExtra("name");

                if (mVersion >= 0)
                    args.add("version=" + mVersion);

                if (name != null)
                    args.add("name=" + name);
            }

            KeyringIdentity identity = ServalBatPhoneApplication.getContext().server.getIdentity();

            ServalDCommand.ManifestResult result = ServalDCommand.rhizomeAddFile(mPayloadFile,
                    mManifestFile, null, identity.sid, null, args.toArray(new String[args.size()]));

            mManifest = intent.getStringExtra("save_manifest");
            if (mManifest != null) {
                // save the new manifest here, so the caller can use it to
                // update a file
                mManifestFile = new File(mManifest);
                OutputStream out = new FileOutputStream(mManifestFile);
                out.write(result.manifest);
                out.close();
            }
        } catch (Exception e) {
            Log.e(TAG, e.getMessage(), e);
        }
    }

}
