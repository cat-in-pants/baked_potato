import 'package:flutter/material.dart';
import 'package:getwidget/getwidget.dart';

void main() {
  runApp(const MyApp());
}

class MyApp extends StatelessWidget {
  const MyApp({super.key});

  @override
  Widget build(BuildContext context) {
    return const MaterialApp(
      debugShowCheckedModeBanner: false,
      home: RegisterForm(),
    );
  }
}

class RegisterForm extends StatefulWidget {
  const RegisterForm({super.key});

  @override
  State<RegisterForm> createState() => _RegisterFormState();
}

class _RegisterFormState extends State<RegisterForm> {
  late TextEditingController _loginController;
  late TextEditingController _passwordController;
  late TextEditingController _confirmPasswordController;

  String? _loginErrorText;
  String? _passwordErrorText;
  String? _confirmPasswordErrorText;

  final Color _customGreen = const Color.fromARGB(255, 86, 195, 74);

  @override
  void initState() {
    super.initState();
    _loginController = TextEditingController();
    _passwordController = TextEditingController();
    _confirmPasswordController = TextEditingController();
  }

  @override
  void dispose() {
    _loginController.dispose();
    _passwordController.dispose();
    _confirmPasswordController.dispose();
    super.dispose();
  }

  void _validateLogin(String login) {
    setState(() {
      if (login.isEmpty) {
        _loginErrorText = 'логин не может быть пустым';
      } else if (login.length < 4) {
        _loginErrorText = 'логин должен быть не короче 4 символов';
      } else if (login.length > 12) {
        _loginErrorText = 'логин должен быть не длиннее 12 символов';
      } else if (login.contains(RegExp(r'[!@#<>?":_`~;[\]\\|=+)(*&^%0-9-]'))) {
        _loginErrorText = 'логин не должен содержать специальные символы';
      } else if (login.contains(' ')) {
        _loginErrorText = 'логин не должен содержать пробелы';
      } else {
        _loginErrorText = null;
      }
    });
  }

  void _validatePassword(String password) {
    setState(() {
      if (password.isEmpty) {
        _passwordErrorText = 'пароль не может быть пустым';
      } else if (password.length < 8) {
        _passwordErrorText = 'пароль должен быть не короче 8 символов';
      } else if (!password.contains(RegExp(r'[0-9]'))) {
        _passwordErrorText = 'пароль должен содержать хотя бы одну цифру';
      } else if (!password.contains(RegExp(r'[A-Z]'))) {
        _passwordErrorText = 'пароль должен содержать хотя бы одну заглавную букву';
      } else if (!password.contains(RegExp(r'[a-z]'))) {
        _passwordErrorText = 'пароль должен содержать хотя бы одну строчную букву';
      } else if (!password.contains(RegExp(r'[!@#\$%^&*(),.?":{}|<>]'))) {
        _passwordErrorText = 'пароль должен содержать хотя бы один специальный символ';
      } else {
        _passwordErrorText = null;
      }
    });
  }

  void _validateConfirmPassword(String confirmPassword) {
    setState(() {
      if (confirmPassword.isEmpty) {
        _confirmPasswordErrorText = 'подтвердите пароль';
      } else if (confirmPassword != _passwordController.text) {
        _confirmPasswordErrorText = 'пароли не совпадают';
      } else {
        _confirmPasswordErrorText = null;
      }
    });
  }

  void _register(BuildContext context) {
    _validateLogin(_loginController.text);
    _validatePassword(_passwordController.text);
    _validateConfirmPassword(_confirmPasswordController.text);
    
    if (_loginErrorText == null && 
        _passwordErrorText == null && 
        _confirmPasswordErrorText == null) {
      
      GFToast.showToast(
        'Пользователь с логином "${_loginController.text}" успешно зарегистрирован',
        context,
        backgroundColor: GFColors.SUCCESS,
        toastPosition: GFToastPosition.BOTTOM,
      );
      
      _loginController.clear();
      _passwordController.clear();
      _confirmPasswordController.clear();
      
    } else {
      String errorMessage = _loginErrorText ?? 
                           _passwordErrorText ?? 
                           _confirmPasswordErrorText ?? 
                           'Проверьте правильность заполнения полей';
      
      GFToast.showToast(
        errorMessage,
        context,
        backgroundColor: GFColors.DANGER,
        toastPosition: GFToastPosition.BOTTOM,
      );
    }
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text('Регистрация пользователя'),
        backgroundColor: _customGreen,
      ),
      body: Padding(
        padding: const EdgeInsets.all(16.0),
        child: SingleChildScrollView(
          child: Column(
            children: [
              GFCard(
                content: Column(
                  children: [
                    TextField(
                      controller: _loginController,
                      onChanged: _validateLogin,
                      onSubmitted: (_) => _register(context),
                      decoration: InputDecoration(
                        labelText: 'Логин',
                        hintText: 'Введите логин',
                        errorText: _loginErrorText,
                        border: const OutlineInputBorder(),
                        prefixIcon: Icon(Icons.person, color: _customGreen),
                      ),
                    ),
                    const SizedBox(height: 15),
                    
                    TextField(
                      controller: _passwordController,
                      onChanged: _validatePassword,
                      obscureText: true,
                      decoration: InputDecoration(
                        labelText: 'Пароль',
                        hintText: 'Введите пароль',
                        errorText: _passwordErrorText,
                        border: const OutlineInputBorder(),
                        prefixIcon: Icon(Icons.lock, color: _customGreen),
                      ),
                    ),
                    const SizedBox(height: 15),
                    
                    TextField(
                      controller: _confirmPasswordController,
                      onChanged: _validateConfirmPassword,
                      obscureText: true,
                      decoration: InputDecoration(
                        labelText: 'Подтверждение пароля',
                        hintText: 'Повторите пароль',
                        errorText: _confirmPasswordErrorText,
                        border: const OutlineInputBorder(),
                        prefixIcon: Icon(Icons.lock_outline, color: _customGreen),
                      ),
                    ),
                    const SizedBox(height: 20),
                    
                    GFButton(
                      onPressed: () => _register(context),
                      text: "Зарегистрироваться",
                      blockButton: true,
                      color: _customGreen,
                      shape: GFButtonShape.pills,
                    ),
                  ],
                ),
              ),
            ],
          ),
        ),
      ),
    );
  }
}
