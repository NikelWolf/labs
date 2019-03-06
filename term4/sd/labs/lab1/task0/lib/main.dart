import 'package:flutter/material.dart';

void main() => runApp(Lab1Task0App());

class Lab1Task0App extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    // TODO: implement build
    return MaterialApp(
      title: 'MIREA SD Lab1 Task 0',
      debugShowCheckedModeBanner: false,
      home: HomePage(),
      theme: ThemeData.dark(),
    );
  }
}

class HomePage extends StatefulWidget {
  @override
  State<StatefulWidget> createState() => _HomePageState();
}

class _HomePageState extends State<HomePage> {
  int _pushedCounter = 0;

  void incrementCounter() {
    setState(() {
      _pushedCounter++;
    });
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text('Home Page'),
      ),
      body: Container(
        child: Center(
            child: Column(
          mainAxisAlignment: MainAxisAlignment.center,
          children: <Widget>[
            Padding(
              padding: EdgeInsets.all(8.0),
              child: Text(
                'button pushed $_pushedCounter times',
                style: const TextStyle(fontSize: 18.0),
              ),
            ),
            Padding(
              padding: EdgeInsets.all(8.0),
              child: FloatingActionButton(
                onPressed: () {
                  incrementCounter();
                },
                backgroundColor: Colors.blueGrey,
              ),
            )
          ],
        )),
      ),
    );
  }
}
