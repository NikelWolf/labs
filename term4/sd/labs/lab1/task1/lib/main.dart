import 'package:flutter/material.dart';

void main() => runApp(Lab1Task1App());

String getNumberAsText(int number) {
  const numerals = <String>[
    "",
    "one",
    "two",
    "three",
    "four",
    "five",
    "six",
    "seven",
    "eight",
    "nine"
  ];
  const decades = <String>[
    "",
    "ten",
    "twenty",
    "thirty",
    "forty",
    "fifty",
    "sixty",
    "seventy",
    "eighty",
    "ninety"
  ];
  const tenDecades = <String>[
    "",
    "eleven",
    "twelve",
    "thirteen",
    "fourteen",
    "fifteen",
    "sixteen",
    "seventeen",
    "eighteen",
    "nineteen"
  ];

  if (number < 0) {
    return "less than zero";
  } else if (number == 0) {
    return "zero";
  } else if (number == 1000000) {
    return "million";
  } else if (number > 1000000) {
    return "more than million";
  }

  var result = "";
  var checkNumber = number ~/ 100000;
  if (checkNumber != 0) {
    result += numerals[checkNumber] + " hundred ";
  }
  number %= 100000;
  checkNumber = number ~/ 1000;
  if (checkNumber != 0) {
    if (result != "") {
      result += "and ";
    }

    if (checkNumber > 10 && checkNumber < 20) {
      result += tenDecades[checkNumber % 10] + " ";
    } else {
      if (checkNumber ~/ 10 != 0) {
        result += decades[checkNumber ~/ 10] + " ";
      }
      if (checkNumber % 10 != 0) {
        result += numerals[checkNumber % 10] + " ";
      }
    }
  }
  if (result != "") {
    result += "thousand ";
  }
  number %= 1000;
  checkNumber = number ~/ 100;
  if (checkNumber != 0) {
    result += numerals[checkNumber] + " hundred ";
  }
  number %= 100;
  checkNumber = number;
  if (checkNumber != 0) {
    if (result != "") {
      result += "and ";
    }

    if (checkNumber > 10 && checkNumber < 20) {
      result += tenDecades[checkNumber % 10] + " ";
    } else {
      if (checkNumber ~/ 10 != 0) {
        result += decades[checkNumber ~/ 10] + " ";
      }
      if (checkNumber % 10 != 0) {
        result += numerals[checkNumber % 10] + " ";
      }
    }
  }

  return result;
}

class Lab1Task1App extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'MIREA SD Lab 1 Task 1',
      debugShowCheckedModeBanner: false,
      home: ImagePage(),
      routes: <String, WidgetBuilder>{
        '/list': (BuildContext context) => ListPage(),
      },
      theme: ThemeData.dark(),
    );
  }
}

class ImagePage extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    Future.delayed(Duration(seconds: 2), () {
      Navigator.of(context).pushReplacementNamed('/list');
    });

    return Scaffold(
      appBar: AppBar(
        title: Text('Image page'),
      ),
      body: Container(
        decoration: BoxDecoration(
            image:
                DecorationImage(image: AssetImage("assets/images/gopher.png"))),
      ),
    );
  }
}

class ListPage extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(title: Text('Numbers list page')),
      body: ListView.builder(
        itemBuilder: (context, i) {
          return Ink(
              color: i.isEven ? Color(0xFFCCCCCC) : Color(0xFFFFFFFF),
              child: ListTile(
                  leading: Icon(Icons.code, color: Colors.green),
                  title: Text(
                    getNumberAsText(i + 1),
                    style: TextStyle(fontSize: 18.0, color: Color(0xFF000000)),
                  )));
        },
        itemCount: 1000000,
      ),
    );
  }
}
