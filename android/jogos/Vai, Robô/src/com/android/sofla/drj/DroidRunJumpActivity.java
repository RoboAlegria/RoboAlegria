package com.android.sofla.drj;

import android.app.Activity;
import android.content.SharedPreferences;
import android.os.Bundle;

import com.android.sofla.drj.DroidRunJumpView.DroidRunJumpThread;


public class DroidRunJumpActivity extends Activity {
	
	public static final String PREFS_NAME = "DRJPrefsFile";
	
	DroidRunJumpView drjView;
	DroidRunJumpThread drjThread;
	
    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);        
        setContentView(R.layout.main);        
        drjView = (DroidRunJumpView) findViewById(R.id.droidrunjump);                       
    }
    
    @Override
    protected void onPause() {
    	super.onPause();

    	SharedPreferences settings = getSharedPreferences(PREFS_NAME, 0);
       	SharedPreferences.Editor editor = settings.edit();
       	
       	drjThread = drjView.getThread();
       	       	    	
       	// if player wants to quit then reset the game
    	if (isFinishing()) {
    		drjThread.resetGame();
    	}
    	else {	    	
    		drjThread.pause();
    	}
    	
       	drjThread.saveGame(editor);
    }
    
    @Override
    protected void onResume() {
    	super.onResume();    
    	// restore game
    	drjThread = drjView.getThread();    
	    SharedPreferences settings = getSharedPreferences(PREFS_NAME, 0);
	   	drjThread.restoreGame(settings);  
    }   
}