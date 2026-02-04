import 'package:flutter/material.dart';

class CounterWidget extends StatefulWidget {
  const CounterWidget({super.key});

  @override
  State<CounterWidget> createState() => _CounterWidgetState();
}

class _CounterWidgetState extends State<CounterWidget> {
  int _counter = 0;
  bool _isLiked = false;

  void _toggleLike() {
    setState(() {
      if (_isLiked) {
        _counter = 0;
        _isLiked = false;
      } else {
        _counter = 1;
        _isLiked = true;
      }
    });
  }

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      debugShowCheckedModeBanner: false,
      home: Scaffold(
        appBar: AppBar(
          title: const Text('Счетчик'),
          backgroundColor: Colors.cyan,
        ),
        body: Center(
          child: Column(
            mainAxisAlignment: MainAxisAlignment.center,
            children: [
              const Text(
                'Значение счетчика: ',
                style: TextStyle(fontSize: 20),
              ),
              const SizedBox(height: 10),
              Text(
                '$_counter',
                style: const TextStyle(fontSize: 48, fontWeight: FontWeight.bold),
              ),
            ],
          ),
        ),
        floatingActionButton: IconButton(
          onPressed: _toggleLike,
          iconSize: 40,
          icon: Icon(
            Icons.favorite,
            color: _isLiked ? Colors.red : Colors.grey,
          ),
        ),
      ),
    );
  }
} 
