#include <unordered_map>
#include <string>
#include <vector>
#include <utility>

struct Level {
	std::pair<int,int> Size;
	std::vector<int> Tiles;
	unsigned char Behaviour; //<0>=block, <1>=editable?...
};

class Map {

	std::vector<Level> Levels;
	int minLevel;
	std::unordered_map<int, std::string> Tilesets;

	public:
	Map(const std::string& MapFile);
	void Reload(const std::string& MapFile);

	std::unordered_map<int, std::string>* getGidToName();
	Level* getLevel(int Level);

};
