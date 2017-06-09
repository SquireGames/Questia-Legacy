#ifndef SV_TILEENGINE_H
#define SV_TILEENGINE_H

#include <vector>

#include "SFML/Window.hpp"

#include "QuestiaEng/TileEngine/TileMap.h"

#include "QuestiaEng/Utl/Utl.h"
#include "QuestiaEng/Utl/Type/Vector2.h"
#include "QuestiaEng/Utl/Type/Vector2.h"
#include "QuestiaEng/Utl/SaveFile.h"
#include "QuestiaEng/Utl/FileData.h"

#include "QuestiaEng/TileEngine/Tile.h"

#include "QuestiaEng/Utl/TextureAtlas.h"


struct TileTransform
{
	TileTransform(std::string texturePath):texturePath(texturePath) {}
	std::string texturePath;
	//(-1, -1) means sprite size
	utl::Vector2i tileSize = utl::Vector2i(-1, -1);
	//only 0, 90, 180, 270 are valid
	int degrees = 0;
	//only x, y, b(both), and n are valid
	char flip = 'n';
};

class SV_TileEngine
{
public:
	//ctor + dtor
	SV_TileEngine(ResourceManager& resourceManager);
	~SV_TileEngine();

	///game
	//loads the TileMap with tileKey and tileMap, loads texture either into Tile's in tileMap or ResourceManager texture TILESTORAGE
	TileMap openMap(const std::string& mapName, sf::RenderWindow& window, TileMap::TextureMode textureMode, TileMap::TileMode tileMode);

	///editor
	//creating map
	bool createMap(const std::string& mapName, unsigned int width, unsigned int height, unsigned int layers);
	TileMap editMap(const std::string& mapName, sf::RenderWindow& window);
	//TODO implement this
	void changeMapDimensions(const std::string& mapName, unsigned int width, unsigned int height, unsigned int layers);
	//saving map and tiles used
	void saveMap(const std::string& mapName, const std::vector <int>& tileMap, unsigned int width, unsigned int height, unsigned int layers, const std::map<int, Tile>& tilePairs);
	
private:
	std::vector <std::pair <int, std::string> > getTileLocations(const std::string& fileDir, TileMap::TextureMode textureMode);
	//loads TileMap with tileKey, and if TileMode = Batch, loads tileAtlas texture into TILESTORAGE in resourceManager
	void loadTiles(std::vector <std::pair <int, std::string> >& tileLocations, TileMap& mapData, sf::RenderWindow& window);
	//loads chunks if in batch mode, validates all sprites in sprite mode
	void loadRenderData(TileMap& mapData);
	
	//for getting coordinates
	int getTile(unsigned int x, unsigned int y, unsigned int layer, TileMap& tileMap);
	int getChunk(unsigned int x, unsigned int y, unsigned int layer, TileMap& tileMap);

	///names of items
	//mapInfo
	const std::string name_width = "width";
	const std::string name_height = "height";
	const std::string name_layers = "layers";

	//for tilework
	ResourceManager& resourceManager;

	//saves textures in 1 sheet
	TextureAtlas textureAtlas;

	const std::string file_mapInfo =   "/mapInfo.txt";
	const std::string file_tilesUsed = "/tilesUsed.txt";
	const std::string file_map =       "/map.txt";
};

#endif // SV_TILEENGINE_H
