import 'package:flutter/material.dart';

void main() => runApp(const MyApp());

class MyApp extends StatelessWidget {
  const MyApp({super.key});

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'редактор профиля',
      theme: ThemeData(primarySwatch: Colors.blue),
      home: const ProfileScreen(),
    );
  }
}

class ProfileScreen extends StatefulWidget {
  const ProfileScreen({super.key});

  @override
  State<ProfileScreen> createState() => _ProfileScreenState();
}

class _ProfileScreenState extends State<ProfileScreen> {
  String name = 'шуречка';
  String status = 'мяу';

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(title: const Text('профиль')),
      body: Center(
        child: Column(
          mainAxisAlignment: MainAxisAlignment.center,
          children: [
            CircleAvatar(
              radius: 50,
              child: Text(
                      name[0],
                      style: const TextStyle(fontSize: 40),
                    ),
            ),
            const SizedBox(height: 16),
            Text(name, style: const TextStyle(fontSize: 24)),
            const SizedBox(height: 8),
            Text(status, style: const TextStyle(fontSize: 16)),
            const SizedBox(height: 32),
            ElevatedButton(
              onPressed: () async {
                final result = await Navigator.push(
                  context,
                  MaterialPageRoute(
                    builder: (context) => EditProfileScreen(
                      currentName: name,
                      currentStatus: status,
                    ),
                  ),
                );
                if (result != null && result is Map<String, String>) {
                  setState(() {
                    name = result['name']!;
                    status = result['status']!;
                  });
                }
              },
              child: const Text('редактировать'),
            ),
          ],
        ),
      ),
    );
  }
}

class EditProfileScreen extends StatelessWidget {
  final String currentName;
  final String currentStatus;

  const EditProfileScreen({
    super.key,
    required this.currentName,
    required this.currentStatus,
  });

  @override
  Widget build(BuildContext context) {
    final nameController = TextEditingController(text: currentName);
    final statusController = TextEditingController(text: currentStatus);

    return Scaffold(
      appBar: AppBar(title: const Text('редактирование профиля')),
      body: Padding(
        padding: const EdgeInsets.all(16.0),
        child: Column(
          children: [
            TextField(
              controller: nameController,
              decoration: const InputDecoration(labelText: 'имя'),
            ),
            const SizedBox(height: 16),
            TextField(
              controller: statusController,
              decoration: const InputDecoration(labelText: 'статус'),
            ),
            const SizedBox(height: 32),
            ElevatedButton(
              onPressed: () {
                final newData = {
                  'name': nameController.text,
                  'status': statusController.text,
                };
                Navigator.pop(context, newData);
              },
              child: const Text('сохранить'),
            ),
          ],
        ),
      ),
    );
  }
}
