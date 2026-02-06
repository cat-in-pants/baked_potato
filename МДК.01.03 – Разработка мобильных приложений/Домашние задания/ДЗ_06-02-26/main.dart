import 'package:flutter/material.dart';
import 'package:getwidget/getwidget.dart';

void main() {
  runApp(const MyApp());
}

class MyApp extends StatelessWidget {
  const MyApp({Key? key}) : super(key: key);

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'Обновление статуса',
      debugShowCheckedModeBanner: false,
      theme: ThemeData(primarySwatch: Colors.green),
      home: StatusUpdateScreen(),
    );
  }
}

class StatusUpdateScreen extends StatefulWidget {
  @override
  State<StatusUpdateScreen> createState() => _StatusUpdateScreenState();
}

class _StatusUpdateScreenState extends State<StatusUpdateScreen> {
  final List<String> _statuses = ["отдыхаю", "работаю", "в отпуске", "не в сети"];
  final List<Color> _statusColors = [Colors.green, Colors.cyan, Colors.orange, Colors.grey];

  int _currentIndex = 0;
  Color _cardColor = Colors.green;

  void _cycleStatus() {
    setState(() {
      _currentIndex = (_currentIndex + 1) % _statuses.length;
      _cardColor = _statusColors[_currentIndex];
    });
  }

  void _changeBackgroundColor(Color color) {
    setState(() {
      _cardColor = color;
    });
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(title: const Text('Обновление статуса')),      body: Center(
        child: Padding(
          padding: const EdgeInsets.all(16.0),
          child: GFCard(
            color: _cardColor,
            content: Column(
              mainAxisSize: MainAxisSize.min,
              children: [
                Text(
                  "Профиль пользователя",
                  style: const TextStyle(fontSize: 18, fontWeight: FontWeight.bold),
                  textAlign: TextAlign.center,
                ),
                const SizedBox(height: 12),
                Text(
                  "Текущий статус: ${_statuses[_currentIndex]}",
                  style: const TextStyle(fontSize: 16),
                ),
                const SizedBox(height: 20),
                GFButton(
                  onPressed: _cycleStatus,
                  text: "Сменить статус",
                  fullWidthButton: true,
                ),
                const SizedBox(height: 20),
                Wrap(
                  spacing: 10,
                  runSpacing: 10,
                  children: [
                    GFButton(
                      onPressed: () => _changeBackgroundColor(Colors.blue),
                      color: Colors.blue,
                      text: "Синий",
                      textColor: Colors.white,
                    ),
                    GFButton(
                      onPressed: () => _changeBackgroundColor(Colors.purple),
                      color: Colors.purple,
                      text: "Фиолетовый",
                      textColor: Colors.white,
                    ),
                    GFButton(
                      onPressed: () => _changeBackgroundColor(Colors.pink),
                      color: Colors.pink,
                      text: "Розовый",
                      textColor: Colors.white,
                    ),
                  ],
                ),              ],
            ),
          ),
        ),
      ),
    );
  }
}
