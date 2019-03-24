import 'dart:convert';
import 'package:dio/dio.dart';
import 'package:flutter/material.dart';

import './tech.dart';

class _StartPageState extends State<StartPage> {
  static const String _techFileUrl =
      'https://raw.githubusercontent.com/wesleywerner/ancient-tech/02decf875616dd9692b31658d92e64a20d99f816/src/data/techs.ruleset.json';

  final String loadingErrorMessage = 'Error while loading tech list';
  final String retryLabel = 'Try again';
  final Duration messageDuration = Duration(seconds: 10);

  final String pageTitle = 'Loading Page';
  final double titleFontSize = 22.0;

  bool error = false;
  BuildContext _scaffoldContext;

  @override
  Widget build(BuildContext context) {
    if (!error) {
      _downloadTechAndChangePage();
    }

    return Scaffold(
      appBar: AppBar(
        title: ListTile(
          title: Text(
            pageTitle,
            style: TextStyle(fontSize: titleFontSize),
          ),
          trailing: error ? Icon(Icons.error) : CircularProgressIndicator(),
        ),
      ),
      body: Builder(
        builder: (context) {
          _scaffoldContext = context;
          return Container(
            decoration: BoxDecoration(
              image: DecorationImage(
                image: AssetImage(
                  "res/assets/images/gopher.png",
                ),
              ),
            ),
          );
        },
      ),
    );
  }

  void _downloadTechAndChangePage() async {
    try {
      var response = await Dio().get(_techFileUrl);
      var techList = TechList.fromJson(
          (jsonDecode(response.data) as List<dynamic>).sublist(1));
      Navigator.of(this.context)
          .pushReplacementNamed('/list', arguments: techList);
    } on DioError catch (_) {
      final snackBar = _buildSnackBar();
      Scaffold.of(_scaffoldContext).showSnackBar(snackBar);

      setState(() {
        error = true;
      });
    }
  }

  SnackBar _buildSnackBar() {
    return SnackBar(
      content: Text(loadingErrorMessage),
      duration: messageDuration,
      action: SnackBarAction(
        label: retryLabel,
        onPressed: () {
          setState(() {
            error = false;
          });
        },
      ),
    );
  }
}

class StartPage extends StatefulWidget {
  @override
  _StartPageState createState() => _StartPageState();
}
