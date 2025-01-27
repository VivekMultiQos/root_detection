package com.example.ndkdemo

import android.os.Bundle
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.compose.foundation.layout.*
import androidx.compose.foundation.text.KeyboardActions
import androidx.compose.foundation.text.KeyboardOptions
import androidx.compose.material3.*
import androidx.compose.runtime.*
import androidx.compose.ui.Alignment
import androidx.compose.ui.ExperimentalComposeUiApi
import androidx.compose.ui.Modifier
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.platform.LocalSoftwareKeyboardController
import androidx.compose.ui.text.TextStyle
import androidx.compose.ui.text.input.ImeAction
import androidx.compose.ui.text.input.KeyboardType
import androidx.compose.ui.text.input.TextFieldValue
import androidx.compose.ui.text.style.TextAlign
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import com.example.ndkdemo.ui.theme.NDKDemoTheme

class MainActivity : ComponentActivity() {

    private external fun isDeviceRooted(): Boolean

    companion object {
        init {
            System.loadLibrary("ndkdemo")
        }
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContent {
            var isRooted by remember { mutableStateOf(false) }
            var isInitial by remember { mutableStateOf(true) }

            NDKDemoTheme {
                Surface(
                    modifier = Modifier.fillMaxSize(),
                    color = MaterialTheme.colorScheme.background
                ) {
                    Column(
                        modifier = Modifier
                            .fillMaxSize()
                            .padding(
                                WindowInsets.systemBars
                                    .asPaddingValues()
                            ),
                        horizontalAlignment = Alignment.CenterHorizontally,
                        verticalArrangement = Arrangement.Center
                    ) {

                        if (isInitial) {
                            Text(
                                text = "Welcome to the Device Root Checker!",
                                textAlign = TextAlign.Center,
                                style = MaterialTheme.typography.headlineMedium
                            )
                        } else {
                            Text(
                                text = if (isRooted) "Device is Rooted" else "Device is Not Rooted",
                                style = TextStyle(
                                    fontSize = 24.sp,
                                    color = if (isRooted) Color.Red else Color.Green
                                )
                            )
                        }
                        Spacer(modifier = Modifier.height(20.dp))
                        Button(onClick = {
                            isInitial = false
                            isRooted = isDeviceRooted()
                        }) {
                            Text("Check if Device is Rooted")
                        }
                    }
                }
            }
        }
    }
}
