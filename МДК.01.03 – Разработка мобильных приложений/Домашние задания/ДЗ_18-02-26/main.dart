import 'dart:math';
import 'package:flutter/material.dart';

void main() {
  runApp(const MyApp());
}

class MyApp extends StatelessWidget {
  const MyApp({super.key});

  @override
  Widget build(BuildContext context) {
    return const MaterialApp(
      debugShowCheckedModeBanner: false,
      home: FirstScreen(),
    );
  }
}

class FirstScreen extends StatefulWidget {
  const FirstScreen({super.key});

  @override
  State<FirstScreen> createState() => _FirstScreenState();
}

class _FirstScreenState extends State<FirstScreen> {
  final TextEditingController controller =
      TextEditingController(text: 'Валера стыд и позор');

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(),
      body: Padding(
        padding: const EdgeInsets.all(20),
        child: Column(
          mainAxisAlignment: MainAxisAlignment.center,
          children: [
            TextField(
              controller: controller,
              decoration: const InputDecoration(
                border: OutlineInputBorder(),
              ),
            ),
            const SizedBox(height: 20),
            SizedBox(
              width: double.infinity,
              child: ElevatedButton(
                onPressed: () {
                  Navigator.push(
                    context,
                    MaterialPageRoute(
                      builder: (_) => SecondScreen(text: controller.text),
                    ),
                  );
                },
                child: const Text('Перейти'),
              ),
            ),
          ],
        ),
      ),
    );
  }
}

class SecondScreen extends StatefulWidget {
  final String text;

  const SecondScreen({super.key, required this.text});

  @override
  State<SecondScreen> createState() => _SecondScreenState();
}

class _SecondScreenState extends State<SecondScreen> {
  final List<Color> colors = [Colors.red, Colors.blue, Colors.green];
  late Color textColor;
  late Color backgroundColor;

  @override
  void initState() {
    super.initState();
    textColor = colors[Random().nextInt(3)];
    backgroundColor = textColor;
  }

  void changeColor(Color color) {
    setState(() {
      backgroundColor = color;
    });
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(),
      backgroundColor: backgroundColor,
      body: Column(
        children: [
          Expanded(
            child: Center(
              child: Text(
                widget.text,
                style: TextStyle(
                  fontSize: 36,
                  fontWeight: FontWeight.bold,
                  color: textColor,
                ),
              ),
            ),
          ),
          Padding(
            padding: const EdgeInsets.only(bottom: 40),
            child: Row(
              mainAxisAlignment: MainAxisAlignment.spaceEvenly,
              children: [
                GestureDetector(
                  onTap: () => changeColor(Colors.red),
                  child: Container(
                    width: 70,
                    height: 50,
                    color: Colors.red,
                  ),
                ),
                GestureDetector(
                  onTap: () => changeColor(Colors.blue),
                  child: Container(
                    width: 70,
                    height: 50,
                    color: Colors.blue,
                  ),
                ),
                GestureDetector(
                  onTap: () => changeColor(Colors.green),
                  child: Container(
                    width: 70,
                    height: 50,
                    color: Colors.green,
                  ),
                ),
              ],
            ),
          ),
        ],
      ),
    );
  }
}
