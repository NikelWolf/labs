import 'package:flutter/material.dart';

import './tech.dart';
import './list_page.dart';
import './start_page.dart';
import './swipe_page.dart';

void main() => runApp(Lab2App());

class Lab2App extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'MIREA SD Lab 2',
      debugShowCheckedModeBanner: false,
      home: StartPage(),
      theme: ThemeData.dark(),
      onGenerateRoute: _getRoute,
    );
  }
}

Route<dynamic> _getRoute(RouteSettings settings) {
  switch (settings.name) {
    case '/list':
      return _buildRoute(
          settings, ListPage(techList: settings.arguments as TechList));
    case '/pager':
      var techList = (settings.arguments as List<dynamic>)[0] as TechList;
      var techIndex = (settings.arguments as List<dynamic>)[1] as int;
      return _buildRoute(
          settings, SwipePage(techList: techList, techIndex: techIndex));
    default:
      return null;
  }
}

MaterialPageRoute _buildRoute(RouteSettings settings, Widget builder) {
  return MaterialPageRoute(
    settings: settings,
    builder: (context) => builder,
  );
}
