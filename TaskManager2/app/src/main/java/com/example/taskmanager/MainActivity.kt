package com.example.taskmanager

import android.os.Bundle
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.activity.enableEdgeToEdge
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.padding
import androidx.compose.material3.Scaffold
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.ui.Modifier
import androidx.compose.ui.tooling.preview.Preview
import com.example.taskmanager.ui.theme.TaskManagerTheme
import androidx.appcompat.app.AppCompatActivity
import kotlinx.android.synthetic.main.activity_main.


class MainActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        val tasks = listOf(
            Task(1, "Задача номер 3", "Низкий", "Бессрочно"),
            Task(2, "Задача номер 2", "Средний", "19.03.2020 в 13:34"),
            Task(3, "Задача номер 1", "Низкий", "27.03.2020 в 13:36")
        )

        val adapter = TaskAdapter(this, tasks)
        taskListView.adapter = adapter
    }
}