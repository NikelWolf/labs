
class Tech {
  final String imageName;
  final String techName;
  final String helpText;

  Tech({this.imageName, this.techName, this.helpText});

  factory Tech.fromJson(Map<String, dynamic> parsedJson) {
    return Tech(
      imageName: parsedJson['graphic'],
      techName: parsedJson['name'],
      helpText: parsedJson['helptext'],
    );
  }
}

class TechList {
  final List<Tech> techs;

  TechList({this.techs});

  factory TechList.fromJson(List<dynamic> parsedJson) {
    List<Tech> techs = parsedJson.map((i) => Tech.fromJson(i)).toList();

    return TechList(
      techs: techs,
    );
  }
}
