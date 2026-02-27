import 'package:flutter/material.dart';



void main() {

  runApp(const MyApp());

}



class MyApp extends StatelessWidget {

  const MyApp({super.key});



  @override

  Widget build(BuildContext context) {

    return MaterialApp(

      title: 'Навигация с вкладками',

      theme: ThemeData(primarySwatch: Colors.blue),

      home: const MainNavigationScreen(),

    );

  }

}



class MainNavigationScreen extends StatefulWidget {

  const MainNavigationScreen({super.key});



  @override

  State<MainNavigationScreen> createState() => _MainNavigationScreenState();

}



class _MainNavigationScreenState extends State<MainNavigationScreen> {

  int _selectedIndex = 0;



  final List<Widget> _screens = const [

    HomeScreen(),

    SearchScreen(),

    ProfileScreen(),

  ];



  void _onItemTapped(int index) {

    setState(() {

      _selectedIndex = index;

    });

  }



  @override

  Widget build(BuildContext context) {

    return Scaffold(

      appBar: AppBar(

        title: const Text('Навигация с вкладками'),

      ),

      body: _screens[_selectedIndex],

      bottomNavigationBar: BottomNavigationBar(

        currentIndex: _selectedIndex,

        onTap: _onItemTapped,

        items: const [

          BottomNavigationBarItem(

            icon: Icon(Icons.home),

            label: 'Главная',

          ),

          BottomNavigationBarItem(

            icon: Icon(Icons.search),

            label: 'Поиск',

          ),

          BottomNavigationBarItem(

            icon: Icon(Icons.person),

            label: 'Профиль',

          ),

        ],

      ),

    );

  }

}



class HomeScreen extends StatelessWidget {

  const HomeScreen({super.key});



  final List<Map<String, String>> items = const [

    {

      'title': 'Элемент 1',

      'subtitle': 'Описание элемента 1',

    },

    {

      'title': 'Элемент 2',

      'subtitle': 'Описание элемента 2',

    },

    {

      'title': 'Элемент 3',

      'subtitle': 'Описание элемента 3',

    },

    {

      'title': 'Элемент 4',

      'subtitle': 'Описание элемента 4',

    },

    {

      'title': 'Элемент 5',

      'subtitle': 'Описание элемента 5',

    },

  ];



  @override

  Widget build(BuildContext context) {

    return ListView.builder(

      itemCount: items.length,

      itemBuilder: (context, index) {

        final item = items[index];

        

        return ListTile(

          leading: CircleAvatar(

            child: Text('${index + 1}'),

          ),

          title: Text(item['title']!),

          subtitle: Text(item['subtitle']!),

          trailing: const Icon(Icons.arrow_forward_ios, size: 16),

          

          onTap: () {

            ScaffoldMessenger.of(context).showSnackBar(

              SnackBar(

                content: Text('Нажат ${item['title']}'),

                duration: const Duration(seconds: 1),

              ),

            );

          },

          

          onLongPress: () {

            ScaffoldMessenger.of(context).showSnackBar(

              SnackBar(

                content: Text('Долгое нажатие на ${item['title']}'),

                duration: const Duration(seconds: 1),

              ),

            );

          },

        );

      },

    );

  }

}



class SearchScreen extends StatefulWidget {

  const SearchScreen({super.key});



  @override

  State<SearchScreen> createState() => _SearchScreenState();

}



class _SearchScreenState extends State<SearchScreen> {

  final TextEditingController _searchController = TextEditingController();



  Future<void> _showSearchDialog() async {

    final query = _searchController.text;

    return showDialog(

      context: context,

      builder: (context) {

        return AlertDialog(

          title: const Text('Поисковый запрос'),

          content: Text(query.isEmpty ? 'Пустой запрос' : 'Искать "$query"?'),

          actions: [

            TextButton(

              onPressed: () => Navigator.pop(context),

              child: const Text('OK'),

            ),

          ],

        );

      },

    );

  }



  @override

  Widget build(BuildContext context) {

    return Padding(

      padding: const EdgeInsets.all(16.0),

      child: Column(

        mainAxisAlignment: MainAxisAlignment.start,

        children: [

          TextField(

            controller: _searchController,

            decoration: const InputDecoration(

              labelText: 'Введите запрос',

              border: OutlineInputBorder(),

            ),

          ),

          const SizedBox(height: 16),

          ElevatedButton(

            onPressed: _showSearchDialog,

            child: const Text('Поиск'),

          ),

        ],

      ),

    );

  }

}



class ProfileScreen extends StatelessWidget {

  const ProfileScreen({super.key});



  @override

  Widget build(BuildContext context) {

    return const Center(

      child: Text('Профиль'),

    );

  }

}
