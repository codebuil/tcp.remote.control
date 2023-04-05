package p1.c1.app;

import android.app.*;
import android.os.*;
import android.app.AlertDialog;
import android.app.Activity;
import android.widget.Toast;


import android.app.Activity;
import android.hardware.usb.UsbDeviceConnection;
import android.hardware.usb.UsbManager;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.Toast;

import java.nio.charset.StandardCharsets;

public class MainActivity extends Activity {
    private static final String ACTION_USB_PERMISSION = "com.android.example.USB_PERMISSION";

    private UsbManager usbManager;
    private UsbDeviceConnection usbConnection;

    private Button onOffButton;
    private boolean isOn = false;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        usbManager = (UsbManager) getSystemService(USB_SERVICE);

        onOffButton = findViewById(R.id.on_off_button);
        onOffButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                if (usbConnection == null) {
                    Toast.makeText(MainActivity.this, "USB connection not available", Toast.LENGTH_SHORT).show();
                    return;
                }

                String message = isOn ? "desligado" : "ligado";
                byte[] messageBytes = message.getBytes(StandardCharsets.UTF_8);
                int sentBytes = usbConnection.bulkTransfer(usbEndpoint, messageBytes, messageBytes.length, 1000);
                if (sentBytes < 0) {
                    Toast.makeText(MainActivity.this, "Error sending message", Toast.LENGTH_SHORT).show();
                } else {
                    Toast.makeText(MainActivity.this, "Message sent successfully", Toast.LENGTH_SHORT).show();
                    isOn = !isOn;
                }
            }
        });
    }

    @Override
    protected void onResume() {
        super.onResume();

        // Request permission to access the USB device
        usbManager.requestPermission(usbDevice, PendingIntent.getBroadcast(this, 0, new Intent(ACTION_USB_PERMISSION), 0));
    }

    @Override
    protected void onPause() {
        super.onPause();

        if (usbConnection != null) {
            usbConnection.close();
            usbConnection = null;
        }
    }
}
