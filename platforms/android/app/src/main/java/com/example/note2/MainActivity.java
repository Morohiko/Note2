package com.example.note2;

import android.app.Activity;
import android.content.Intent;
import android.graphics.Color;
import android.net.Uri;
import android.os.Bundle;
import android.text.Editable;
import android.text.TextWatcher;
import android.util.Log;
import android.view.View;
import android.widget.AdapterView;
import android.widget.Button;
import android.widget.CheckBox;
import android.widget.EditText;
import android.widget.ListView;
import android.widget.TextView;

import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;

import java.util.ArrayList;
import java.util.Date;
import java.util.List;

public class MainActivity extends AppCompatActivity {

    // Load the native library on application startup.
    static {
        System.loadLibrary("note_andr_lib");
    }

    // Declare the native method.
    public native String stringFromJNI();

    private static final int REQUEST_CODE_BROWSE = 1;

    // UI Elements
    private Button btnWrite;
    private Button btnRead;
    private Button btnOpen;
    private EditText textEdit;
    private TextView label;
    private EditText editKey;
    private CheckBox checkBoxCustomTime;
    private EditText editCustomTime;
    private ListView treeView; // To simulate the treeWidget

    // Callback interfaces to mimic your Qt function pointers
    private SetFilenameHandler setFilenameHandler;
    private ReadByDateHandler performReadByDateHandler;
    private ReadAllDateHandler performReadAllDateHandler;
    private WriteToFileHandler performWriteToFileHandler;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Bind UI elements
        btnWrite = findViewById(R.id.btnWrite);
        btnRead = findViewById(R.id.btnRead);
        btnOpen = findViewById(R.id.btnOpen);
        textEdit = findViewById(R.id.textEdit);
        label = findViewById(R.id.labeldbg);
        editKey = findViewById(R.id.editKey);
        checkBoxCustomTime = findViewById(R.id.checkBoxCustomTime);
        editCustomTime = findViewById(R.id.editCustomTime);
        treeView = findViewById(R.id.treeView);

        // Disable custom time edit initially and set current time
        editCustomTime.setEnabled(false);
        editCustomTime.setText(new Date().toString());

        // Update the label as text is entered (show text length)
        textEdit.addTextChangedListener(new TextWatcher() {
            @Override
            public void beforeTextChanged(CharSequence s, int start, int count, int after) {
                // Not needed
            }

            @Override
            public void onTextChanged(CharSequence s, int start, int before, int count) {
                label.setText(s.length() + "/999999");
            }

            @Override
            public void afterTextChanged(Editable s) {
                // Not needed
            }
        });

        // Set button click listeners
        btnWrite.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                slotForWriteButton();
            }
        });

        btnOpen.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                slotForOpenButton();
            }
        });

        btnRead.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                slotForReadButton();
            }
        });

        checkBoxCustomTime.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                slotCheckBoxCustomTime();
            }
        });

        // Example: Set default callback implementations (these can be replaced later)
        setCallbacks(new SetFilenameHandler() {
            @Override
            public int setFilename(String filename) {
                // Dummy implementation: log and return success (0)
                Log.d("Note2:SetFilename", "Filename set: " + filename);
                return 0;
            }
        }, new ReadByDateHandler() {
            @Override
            public int readByDate(Date date, String key, StringBuilder output) {
                // Dummy implementation: return sample text based on date
                output.append("Sample text for date: " + date.toString());
                return 0;
            }
        }, new ReadAllDateHandler() {
            @Override
            public int readAllDate(String key, List<Date> dateList) {
                // Dummy implementation: add the current date
                dateList.add(new Date());
                return 0;
            }
        }, new WriteToFileHandler() {
            @Override
            public int writeToFile(String text, boolean isCustomTime, Date datetime, String key) {
                // Dummy implementation: log and return success
                Log.d("Note2:WriteToFile", "Text: " + text + ", CustomTime: " + isCustomTime +
                        ", Date: " + datetime + ", Key: " + key);
                return 0;
            }
        });
    }

    // Mimics slotForWriteButton() from Qt
    private void slotForWriteButton() {
        String text = textEdit.getText().toString();
        boolean isCustomTime = checkBoxCustomTime.isChecked();
        Date datetime = getCustomDateTime();
        String key = getKey();
        int stat = performWriteToFileHandler.writeToFile(text, isCustomTime, datetime, key);
        if (stat != 0) {
            setColorForButton(btnWrite, Color.RED);
        } else {
            setColorForButton(btnWrite, Color.GREEN);
            textEdit.setText("");
        }
    }

    // Mimics slotForOpenButton() from Qt
    private void slotForOpenButton() {
        // Open file picker
        Intent intent = new Intent(Intent.ACTION_GET_CONTENT);
        intent.setType("*/*"); // Allow all file types
        intent.addCategory(Intent.CATEGORY_OPENABLE);
        startActivityForResult(Intent.createChooser(intent, "Select File"), REQUEST_CODE_BROWSE);
    }

    // Mimics slotForReadButton() from Qt
    private void slotForReadButton() {
        List<Date> dateList = new ArrayList<>();
        String key = getKey();
        if (performReadAllDateHandler.readAllDate(key, dateList) == 0) {
            setColorForButton(btnRead, Color.GREEN);
            Log.d("Note2:ReadAllDate", "performReadAllDateHandler success");
        } else {
            setColorForButton(btnRead, Color.RED);
            Log.d("Note2:ReadAllDate", "performReadAllDateHandler failed");
            return;
        }
        // Here you would update your tree view. For demonstration, we simply log the dates.
        for (Date date : dateList) {
            Log.d("Note2:TreeView", "Date: " + date.toString());
        }
        // Set a click listener on the treeView items to mimic reading a specific date
        treeView.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
                // In a real implementation, map the clicked item to a date.
                if (position < dateList.size()) {
                    readByTreeWidgetItem(dateList.get(position));
                }
            }
        });
    }

    // Mimics readByTreeWidgetItem() from Qt
    private void readByTreeWidgetItem(Date date) {
        String key = getKey();
        StringBuilder output = new StringBuilder();
        if (performReadByDateHandler.readByDate(date, key, output) == 0) {
            textEdit.setText(output.toString());
        } else {
            textEdit.setText("Error reading file for date " + date.toString());
        }
    }

    // Returns current custom time; in a real app you might show a Date/Time picker
    private Date getCustomDateTime() {
        return new Date();
    }

    // When the custom time CheckBox is toggled, update the field and enable/disable it
    private void slotCheckBoxCustomTime() {
        editCustomTime.setText(new Date().toString());
        editCustomTime.setEnabled(checkBoxCustomTime.isChecked());
    }

    // Returns the text from the key EditText
    private String getKey() {
        return editKey.getText().toString();
    }

    // Helper method to set a button’s background color
    private void setColorForButton(Button button, int color) {
        button.setBackgroundColor(color);
    }

    // Set the callback implementations (similarly to setCallbacks() in Qt)
    public void setCallbacks(SetFilenameHandler setFilename,
                             ReadByDateHandler performReadByDate,
                             ReadAllDateHandler performReadAllDate,
                             WriteToFileHandler performWriteToFile) {
        this.setFilenameHandler = setFilename;
        this.performReadByDateHandler = performReadByDate;
        this.performReadAllDateHandler = performReadAllDate;
        this.performWriteToFileHandler = performWriteToFile;
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, @Nullable Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        if (requestCode == REQUEST_CODE_BROWSE && resultCode == Activity.RESULT_OK && data != null) {
            Uri fileUri = data.getData();
            if (fileUri != null) {
                String filename = fileUri.toString();
                int retval = setFilenameHandler.setFilename(filename);
                int color = (retval == 0) ? Color.GREEN : Color.RED;
                setColorForButton(btnOpen, color);
            }
        }
    }

    // Callback interface definitions
    public interface SetFilenameHandler {
        int setFilename(String filename);
    }

    public interface ReadByDateHandler {
        int readByDate(Date date, String key, StringBuilder output);
    }

    public interface ReadAllDateHandler {
        int readAllDate(String key, List<Date> dateList);
    }

    public interface WriteToFileHandler {
        int writeToFile(String text, boolean isCustomTime, Date datetime, String key);
    }
}
