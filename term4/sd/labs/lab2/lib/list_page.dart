import 'package:flutter/material.dart';
import 'package:cached_network_image/cached_network_image.dart';

import './tech.dart';

class ListPage extends StatelessWidget {
  static const String _techBaseUrl =
      'https://raw.githubusercontent.com/wesleywerner/ancient-tech/02decf875616dd9692b31658d92e64a20d99f816/src/images/tech';

  final TechList techList;
  ListPage({this.techList});

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text('Tech list page'),
      ),
      body: ListView.builder(
        itemBuilder: (context, index) {
          var tech = techList.techs[index];
          var url = '$_techBaseUrl/${tech.imageName}';

          return _buildListItem(context, index, tech, url);
        },
        itemCount: techList.techs.length,
      ),
    );
  }

  Widget _buildListItem(
      BuildContext context, int index, Tech tech, String url) {
    return Container(
      height: 64,
      child: FlatButton(
        child: ListTile(
          title: Text(tech.techName),
          trailing: CachedNetworkImage(
            imageUrl: url,
            placeholder: (context, url) => CircularProgressIndicator(),
            errorWidget: (context, url, error) {
              return Icon(Icons.error);
            },
            width: 64,
            height: 64,
          ),
        ),
        onPressed: () {
          Navigator.of(context)
              .pushNamed('/pager', arguments: <dynamic>[techList, index]);
        },
      ),
    );
  }
}
