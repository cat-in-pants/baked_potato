import 'package:flutter/material.dart';

void main() {
  runApp(const MyApp());
}

class MyApp extends StatelessWidget {
  const MyApp({super.key});

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'Калькулятор',
      theme: ThemeData(primarySwatch: Colors.blue),
      home: const CalculatorScreen(),
    );
  }
}

class CalculatorScreen extends StatelessWidget {
  const CalculatorScreen({super.key});

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text('Калькулятор'),
        centerTitle: true,
      ),
      body: const CalculatorGrid(),
    );
  }
}

class CalculatorGrid extends StatelessWidget {
  const CalculatorGrid({super.key});

  @override
  Widget build(BuildContext context) {
    return Column(
      children: [
        Expanded(
          child: Container(
            alignment: Alignment.bottomRight,
            padding: const EdgeInsets.all(20),
            child: const Text(
              '0',
              style: TextStyle(fontSize: 48, fontWeight: FontWeight.bold),
            ),
          ),
        ),
        Expanded(
          flex: 3,
          child: GridView.count(
            crossAxisCount: 4,
            childAspectRatio: 1.2,
            mainAxisSpacing: 8,
            crossAxisSpacing: 8,
            padding: const EdgeInsets.all(16),
            children: const [
              _buildGridItem('7', Colors.red),
              _buildGridItem('8', Colors.orange),
              _buildGridItem('9', Colors.yellow),
              _buildGridItem('C', Colors.blueGrey),
              _buildGridItem('4', Colors.lightGreen),
              _buildGridItem('5', Colors.green),
              _buildGridItem('6', Colors.cyan),
              _buildGridItem('÷', Colors.grey),
              _buildGridItem('1', Colors.blue),
              _buildGridItem('2', Colors.deepPurple),
              _buildGridItem('3', Colors.purple),
              _buildGridItem('×', Colors.grey),
              _buildGridItem('0', Colors.pink),
              _buildGridItem('=', Colors.blueGrey),
              _buildGridItem('+', Colors.grey),
              _buildGridItem('-', Colors.grey),
            ],
          ),
        ),
      ],
    );
  }
}

class _buildGridItem extends StatelessWidget {
  final String text;
  final Color color;

  const _buildGridItem(this.text, this.color);

  @override
  Widget build(BuildContext context) {
    return Container(
      decoration: BoxDecoration(
        color: color,
        borderRadius: BorderRadius.circular(8),
      ),
      child: Center(
        child: Text(
          text,
          style: const TextStyle(
            fontSize: 40,
            color: Colors.white,
            fontWeight: FontWeight.bold,
          ),
        ),
      ),
    );
  }
}
