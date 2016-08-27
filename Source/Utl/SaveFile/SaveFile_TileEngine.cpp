#include "SaveFile_TileEngine.h"

SaveFile_TileEngine::SaveFile_TileEngine(ResourceManager& _resourceManager):
    resourceManager(_resourceManager)
    , textureAtlas(_resourceManager)
{

}
SaveFile_TileEngine::~SaveFile_TileEngine()
{
    //dtor
}


MapData SaveFile_TileEngine::openMap(std::string mapName, sf::RenderWindow& window)
{
    //create map
    MapData mapData;

    //make sure directory exists
    if(!utl::doesExist(utl::conjoinString({"Maps/", mapName})))
    {
        throw std::runtime_error (utl::conjoinString({"ERROR: Reading map- Maps/", mapName, " <Utl/SaveFile/SaveFile_TileEngine.cpp>"}));
        return mapData;
    }

    ///mapInfo
    //reads mapInfo
    SaveFile saveFile_mapInfo;
    saveFile_mapInfo.setFilePath(utl::conjoinString({"Maps/", mapName, "/mapInfo.txt"}));
    saveFile_mapInfo.readFile();
    mapData.width  = utl::asInt(saveFile_mapInfo.getItem(name_width));
    mapData.height = utl::asInt(saveFile_mapInfo.getItem(name_height));
    mapData.layers = utl::asInt(saveFile_mapInfo.getItem(name_layers));
    unsigned int totalTiles = mapData.width * mapData.height * mapData.layers;

    ///tileStorage
    textureAtlas.addTexture("1,1",  "Media/Image/Game/Tiles/01/01.png");
    textureAtlas.addTexture("4,21", "Media/Image/Game/Tiles/04/21.png");
    textureAtlas.addTexture("3,4",  "Media/Image/Game/Tiles/03/04.png");
    textureAtlas.addTexture("7,7", "Media/Image/Game/Tiles/TESTING/Arrow.png");

    //now texture exists in resourceManager
    TextureAtlasData compiledTexture = textureAtlas.compileTextures("TILESTORAGE");

    mapData.tileStorage.emplace(std::make_pair(1,1), Tile(window, resourceManager));
    mapData.tileStorage.at(std::make_pair(1,1)).texturePosition = compiledTexture.textureCoords.at("1,1");
    mapData.tileStorage.at(std::make_pair(1,1)).setSize(1,1);
    //temp, only for tileEditor
    mapData.tileStorage.at(std::make_pair(1,1)).tileType = Tile::TileType::sprite;
    mapData.tileStorage.at(std::make_pair(1,1)).setTexture("Media/Image/Game/Tiles/01/01.png");
    mapData.tileStorage.at(std::make_pair(1,1)).setSize(1,1);


    mapData.tileStorage.emplace(std::make_pair(4,21), Tile(window, resourceManager));
    mapData.tileStorage.at(std::make_pair(4,21)).texturePosition = compiledTexture.textureCoords.at("4,21");
    mapData.tileStorage.at(std::make_pair(4,21)).setSize(1,1);
    //temp, only for tileEditor
    mapData.tileStorage.at(std::make_pair(4,21)).tileType = Tile::TileType::sprite;
    mapData.tileStorage.at(std::make_pair(4,21)).setTexture("Media/Image/Game/Tiles/04/21.png");
    mapData.tileStorage.at(std::make_pair(1,1)).setSize(1,1);

    //////////////TEST
    mapData.tileStorage.emplace(std::make_pair(7,7), Tile(window, resourceManager));
    mapData.tileStorage.at(std::make_pair(7,7)).texturePosition = compiledTexture.textureCoords.at("7,7");
    mapData.tileStorage.at(std::make_pair(7,7)).setSize(1,1);
    mapData.tileStorage.at(std::make_pair(7,7)).setRotate(90);
    mapData.tileStorage.at(std::make_pair(7,7)).setFlip('b');
    //temp, only for tileEditor\
    mapData.tileStorage.at(std::make_pair(4,21)).tileType = Tile::TileType::sprite;\
    mapData.tileStorage.at(std::make_pair(4,21)).setTexture("Media/Image/Game/Tiles/04/21.png");\
    mapData.tileStorage.at(std::make_pair(1,1)).setSize(1,1);
    //////////////TEST

    mapData.tileStorage.emplace(std::make_pair(3,4), Tile(window, resourceManager));
    mapData.tileStorage.at(std::make_pair(3,4)).texturePosition = compiledTexture.textureCoords.at("3,4");
    mapData.tileStorage.at(std::make_pair(3,4)).setSize(1,1);

    mapData.tileStorage.emplace(std::make_pair(75,1), Tile(window, resourceManager));
    mapData.tileStorage.at(std::make_pair(75,1)).setTexture("Media/Image/Game/Tiles/75/01.png");
    mapData.tileStorage.at(std::make_pair(75,1)).setSize(1,1);



    ///tileMap
    mapData.tileMap.resize(totalTiles);
    //fill with nil
    std::fill(mapData.tileMap.begin(), mapData.tileMap.end(), utl::Vector2ui(0,0));
    //open map file
    SaveFile saveFile_map;
    saveFile_map.setFilePath(utl::conjoinString({"Maps/", mapName, "/map.txt"}));
    saveFile_map.readFile();
    //get tiles
    std::vector <std::string> tileVector = saveFile_map.getItemList();
    unsigned int tileNumberIterator = 0;
    for(const std::string& tileLine : tileVector)
    {
        std::vector <std::string> tiles = utl::separateString(tileLine, '|');
        for(std::string& tile : tiles)
        {
            //make sure it is not empty
            if(utl::isWithAnyCharacter(tile, ","))
            {
                std::vector <std::string> tileType = utl::separateString(tile, ',');
                if(utl::asInt(tileType[0]) != 0)
                {
                    mapData.tileMap[tileNumberIterator] = {utl::asInt(tileType[0]), utl::asInt(tileType[1])};
                    //std::cout << "tileNumberIterator: " << tileNumberIterator << ", x = " << utl::asInt(tileType[0]) << ", y = " << utl::asInt(tileType[1]) << std::endl;
                }
                tileNumberIterator++;
            }
        }
    }

    //fill with correct tiles
    //mapData.tileMap[getTile(0,0,0, mapData.width, mapData.height)] = {1,1};
    //mapData.tileMap[getTile(1,0,0, mapData.width, mapData.height)] = {1,1};
    //mapData.tileMap[getTile(2,0,0, mapData.width, mapData.height)] = {4,21};
    //mapData.tileMap[getTile(0,1,0, mapData.width, mapData.height)] = {4,21};
    //mapData.tileMap[getTile(0,1,1, mapData.width, mapData.height)] = {75,1};
    //mapData.tileMap[getTile(0,0,1, mapData.width, mapData.height)] = {75,1};

    return mapData;
}

///editor
bool SaveFile_TileEngine::createMap(std::string mapName, unsigned int width, unsigned int height, unsigned int layers)
{
    //file paths
    std::string filePath = utl::conjoinString({"Maps/", mapName});
    const std::string file_mapInfo =   "/mapInfo.txt";
    const std::string file_tilesUsed = "/tilesUsed.txt";
    const std::string file_map =       "/map.txt";

    //make sure not to override any other map
    if(utl::doesExist(filePath))
    {
        return false;
    }
    //make sure directory is created
    if(!utl::createDirectory(filePath))
    {
        return false;
    }

    //create info file
    SaveFile saveFile_mapInfo;
    saveFile_mapInfo.setFilePath(filePath + file_mapInfo);
    saveFile_mapInfo.saveItem(name_width, width);
    saveFile_mapInfo.saveItem(name_height, height);
    saveFile_mapInfo.saveItem(name_layers, layers);
    saveFile_mapInfo.writeFile();

    //create tile info file
    SaveFile saveFile_tilesUsed;
    saveFile_tilesUsed.setFilePath(filePath + file_tilesUsed);
    saveFile_tilesUsed.addItem("nil", "nil");
    saveFile_tilesUsed.writeFile();

    //create map save
    SaveFile saveFile_map;
    saveFile_map.setFilePath(filePath + file_map);
    //get the map string
    const std::string nullTile  =    "0,0|";
    const std::string nullTileEnd  = "0,0";
    std::vector <std::string> tileLine;
    //-1 to account for end
    for(unsigned int it = 0; it != width - 1; it++)
    {
        tileLine.push_back(nullTile);
    }
    tileLine.push_back(nullTileEnd);
    //save map
    for(unsigned int itLayers = 0; itLayers != layers; itLayers++)
    {
        for(unsigned int itHeight = 0; itHeight != height; itHeight++)
        {
            saveFile_map.addItem(utl::conjoinString(tileLine), "");
        }
        //line between layers
        if(itLayers != layers - 1)
        {
            saveFile_map.addItem("", "");
        }
    }

    saveFile_map.writeFile();

    return true;
}

///helper
int SaveFile_TileEngine::getTile(unsigned int x, unsigned int y, unsigned int layer, unsigned int mapWidth, unsigned int mapHeight)
{
    return x + (mapWidth * y) + (layer * mapWidth * mapHeight);
}
