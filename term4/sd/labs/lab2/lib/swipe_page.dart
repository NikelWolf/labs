import 'package:flutter/material.dart';
import 'package:cached_network_image/cached_network_image.dart';

import './tech.dart';

class SwipePage extends StatelessWidget {
  static const String _techBaseUrl =
      'https://raw.githubusercontent.com/wesleywerner/ancient-tech/02decf875616dd9692b31658d92e64a20d99f816/src/images/tech';

  final TechList techList;
  final int techIndex;

  SwipePage({this.techList, this.techIndex});

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text('Swipe page'),
      ),
      body: PageView.builder(
        itemBuilder: (context, index) {
          var tech = techList.techs[index];
          var url = '$_techBaseUrl/${tech.imageName}';

          return _buildPage(tech, url);
        },
        itemCount: techList.techs.length,
        controller: PageController(initialPage: techIndex, keepPage: false),
      ),
    );
  }

  Widget _buildPage(Tech tech, String url) {
    return Center(
      child: SizedBox(
        height: 300,
        child: Card(
          margin: EdgeInsets.symmetric(horizontal: 20),
          child: Column(
            children: [
              SizedBox(
                height: 15,
              ),
              CachedNetworkImage(
                imageUrl: url,
                placeholder: (context, url) => CircularProgressIndicator(),
                errorWidget: (context, url, error) {
                  return Icon(Icons.error);
                },
              ),
              Divider(),
              ListTile(
                title: Text(tech.techName,
                    style: TextStyle(fontWeight: FontWeight.w500)),
                leading: Icon(
                  Icons.feedback,
                ),
              ),
              ListTile(
                title: Text(tech.helpText != null ? tech.helpText : ""),
                leading: Icon(
                  Icons.help,
                ),
              ),
            ],
          ),
        ),
      ),
    );
  }
}
