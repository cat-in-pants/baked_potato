import 'package:flutter/material.dart';



void main() => runApp(const MyApp());



class MyApp extends StatelessWidget {

  const MyApp({super.key});



  @override

  Widget build(BuildContext context) {

    return MaterialApp(

      home: Scaffold(

        backgroundColor: Colors.grey[200],

        body: Center(

          child: SizedBox(

            width: 300,

            height: 400,

            child: ProductCard(),

          ),

        ),

      ),

    );

  }

}



class ProductCard extends StatelessWidget {

  const ProductCard({super.key});



  @override

  Widget build(BuildContext context) {

    return Container(

      width: 300,

      decoration: BoxDecoration(

        color: Colors.white,

        borderRadius: BorderRadius.circular(16),

        boxShadow: [

          BoxShadow(

            color: Colors.black.withOpacity(0.1),

            blurRadius: 10,

            offset: const Offset(0, 4),

          ),

        ],

      ),

      child: Column(

        crossAxisAlignment: CrossAxisAlignment.start,

        children: [

          Stack(

            children: [

              ClipRRect(

                borderRadius: const BorderRadius.vertical(top: Radius.circular(16)),

                child: Image.network(

                  'https://img.icons8.com/liquid-glass-color/1200/c-plus-plus-logo.jpg',

                  height: 200,

                  width: double.infinity,

                  fit: BoxFit.contain,

                ),

              ),

              Positioned(

                top: 12,

                left: 12,

                child: Container(

                  padding: const EdgeInsets.symmetric(horizontal: 8, vertical: 4),

                  decoration: BoxDecoration(

                    color: Colors.red,

                    borderRadius: BorderRadius.circular(4),

                  ),

                  child: const Text(

                    'Скидка 23%',

                    style: TextStyle(

                      color: Colors.white,

                      fontSize: 12,

                      fontWeight: FontWeight.bold,

                    ),

                  ),

                ),

              ),

            ],

          ),

          Padding(

            padding: const EdgeInsets.all(16),

            child: Column(

              crossAxisAlignment: CrossAxisAlignment.start,

              children: [

                const Text(

                  'Автомат по С++',

                  style: TextStyle(

                    fontSize: 18,

                    fontWeight: FontWeight.bold,

                  ),

                ),

                const SizedBox(height: 8),

                Row(

                  mainAxisSize: MainAxisSize.min,

                  children: [

                    ...List.generate(5, (index) {

                      return const Icon(

                        Icons.star,

                        color: Color.fromARGB(255, 0, 199, 60),

                        size: 18,

                      );

                    }),

                    const SizedBox(width: 4),

                    const Text(

                      '4.8',

                      style: TextStyle(

                        fontSize: 12,

                        fontWeight: FontWeight.bold,

                      ),

                    ),

                  ],

                ),

                const SizedBox(height: 8),

                Row(

                  children: [

                    const Text(

                      '\$99.99',

                      style: TextStyle(

                        fontSize: 16,

                        fontWeight: FontWeight.bold,

                      ),

                    ),

                    const SizedBox(width: 8),

                    Text(

                      '\$129.99',

                      style: TextStyle(

                        fontSize: 14,

                        color: Colors.grey[600],

                        decoration: TextDecoration.lineThrough,

                      ),

                    ),

                  ],

                ),

                const SizedBox(height: 16),

                Row(

                  mainAxisAlignment: MainAxisAlignment.spaceBetween,

                  children: [

                    Expanded(

                      child: Container(

                        height: 40,

                        alignment: Alignment.center,

                        decoration: BoxDecoration(

                          color: const Color.fromARGB(255, 71, 180, 89),

                          borderRadius: BorderRadius.circular(8),

                        ),

                        child: const Text(

                          'В корзину',

                          style: TextStyle(

                            color: Colors.white,

                            fontWeight: FontWeight.bold,

                          ),

                        ),

                      ),

                    ),

                    const SizedBox(width: 12),

                    Container(

                      height: 40,

                      width: 40,

                      alignment: Alignment.center,

                      decoration: BoxDecoration(

                        color: const Color.fromARGB(255, 215, 236, 215),

                        borderRadius: BorderRadius.circular(8),

                      ),

                      child: const Icon(

                        Icons.favorite_border,

                        color: Color.fromARGB(255, 145, 158, 147),

                        size: 20,

                      ),

                    ),

                  ],

                ),

              ],

            ),

          ),

        ],

      ),

    );

  }

}
