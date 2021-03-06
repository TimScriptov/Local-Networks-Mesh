package org.servalproject.ui;

import android.content.Intent;
import android.content.SharedPreferences;
import android.content.SharedPreferences.OnSharedPreferenceChangeListener;
import android.os.Bundle;
import android.preference.Preference;
import android.preference.PreferenceActivity;
import android.preference.PreferenceManager;

import org.servalproject.R;
import org.servalproject.ServalBatPhoneApplication;

public class AdhocPreferences extends PreferenceActivity implements
        OnSharedPreferenceChangeListener {
    public static final String EXTRA_PROFILE_NAME = "profile_name";
    private PreferenceManager pm;
    private SharedPreferences prefs;
    private boolean dirty;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        pm = this.getPreferenceManager();

        Intent intent = this.getIntent();
        String name = intent.getStringExtra(EXTRA_PROFILE_NAME);
        pm.setSharedPreferencesName(name);
        prefs = pm.getSharedPreferences();
        this.addPreferencesFromResource(R.xml.adhoc_settings);

        // Disable "Transmit power" if not supported
        if (!ServalBatPhoneApplication.getContext().isTransmitPowerSupported()) {
            findPreference("txpowerpref").setEnabled(false);
        }
    }

    @Override
    protected void onPause() {
        super.onPause();
        prefs.unregisterOnSharedPreferenceChangeListener(this);
        if (dirty) {
            ServalBatPhoneApplication.getContext().nm.control.onAdhocConfigChange();
        }
    }

    private void updateSummary(String key) {
        Preference pref = this.findPreference(key);
        if (pref != null)
            pref.setSummary(prefs.getString(key, null));
    }

    @Override
    protected void onResume() {
        super.onResume();
        prefs.registerOnSharedPreferenceChangeListener(this);
        this.dirty = false;
        for (String key : prefs.getAll().keySet()) {
            updateSummary(key);
        }
    }

    @Override
    public void onSharedPreferenceChanged(SharedPreferences prefs, String key) {
        updateSummary(key);
        dirty = true;
    }
}
