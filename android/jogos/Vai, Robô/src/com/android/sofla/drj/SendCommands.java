package com.android.sofla.drj;

import java.io.InputStream;
import java.net.HttpURLConnection;
import java.net.URL;

import android.os.AsyncTask;

class SendCommands extends AsyncTask<String, Void, String> {

	@Override
    protected void onPreExecute(){
        
    }
	
    @Override
    protected String doInBackground(String... command) {
       // perform your network logic here

    	URL url;
	    HttpURLConnection urlConnection = null;
	    try {
	        url = new URL("http://192.168.201.3:80/?"+command[0]);
	        
	        urlConnection = (HttpURLConnection) url
	                .openConnection();
	        
	        urlConnection.setConnectTimeout(250);
	        
	        urlConnection.setReadTimeout(1);
	        
	        InputStream in = urlConnection.getInputStream();
	        		        
	        urlConnection.disconnect();
	        
	    } catch (Exception e) {
	        e.printStackTrace();
	    } finally {
	        if (urlConnection != null) {
	            urlConnection.disconnect();
	        }    
	    }
    	
    	return "YourResult";
    }
    
}