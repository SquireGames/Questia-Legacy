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

MapData SaveFile_TileEngine::openMap(std::string mapName, sf::RenderWindow& window, TextureMode textureMode, TileMode tileMode)
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

    //get all tile textures
    std::vector <std::pair <int, std::string> > tileLocations;
    switch (textureMode)
    {
    case TextureMode::Map:
        tileLocations = getTileLocations(utl::conjoinString({"Maps/", mapName, "/tileData.txt"}));
        break;
    case TextureMode::All:
        tileLocations = getTileLocations(utl::conjoinString({"Maps/", mapName}));
        break;
    }

    //load tile textures into resourceManager, tileData into mapData.tileStorage
    loadTiles(tileLocations, mapData, tileMode, window);

    ///tileMap
    mapData.tileMap.resize(totalTiles);
    //fill with nil
    std::fill(mapData.tileMap.begin(), mapData.tileMap.end(), 0);
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
            if(utl::isNumber(tile) && utl::asInt(tile) != 0)
            {
                mapData.tileMap[tileNumberIterator] = utl::asInt(tile);
            }
            tileNumberIterator++;
        }
    }

    std::cout << "Tiles: " << tileNumberIterator << std::endl;
    return mapData;
}

std::vector <std::pair <int, std::string> > SaveFile_TileEngine::getTileLocations(std::string filePath)
{
    //emulating file input
    std::vector<std::pair <int, std::string> > tempTiles;
    tempTiles.push_back(std::make_pair(1,  "Media/Image/Game/Tiles/01/01.png"));
    tempTiles.push_back(std::make_pair(22, "Media/Image/Game/Tiles/04/21.png"));
    tempTiles.push_back(std::make_pair(3,  "Media/Image/Game/Tiles/03/04.png"));
    tempTiles.push_back(std::make_pair(4,  "Media/Image/Game/Tiles/TESTING/Arrow.png"));

    return tempTiles;
}

void SaveFile_TileEngine::loadTiles(const std::vector <std::pair <int, std::string> >& tileLocations, MapData& mapData, TileMode tileMode, sf::RenderWindow& window)
{
    //used to hold transform data for each tile
    std::map<int, TileTransform> tileTransform;
    //only used for Batching
    TextureAtlasData compiledTexture = TextureAtlasData(nullptr);

    //loads textures into textureAtlas
    if(tileMode == TileMode::Batch)
    {
        for(auto& tileData : tileLocations)
        {
            const int& tileID = tileData.first;
            const std::string& filePath = tileData.second;

            if(filePath.substr(filePath.length() - 4) == ".png")
            {
                if(!textureAtlas.addTexture(utl::asString(tileData.first), tileData.second))
                {
                    std::cout << "TILEENGINE - Tile: '" << filePath << "' failed to load <Utl/SaveFile/SaveFile_TileEngine.cpp>" << std::endl;
                    textureAtlas.addTexture(utl::asString(tileData.first), "Media/Image/Game/Tiles/Debug/Missing.png");
                }
            }
            else if(filePath.substr(filePath.length() - 4) == ".txt")
            {
                std::string texturePath = filePath;
                texturePath.resize(texturePath.length()-4);
                texturePath = utl::conjoinString({texturePath,".png"});
                if(!textureAtlas.addTexture(utl::asString(tileData.first), texturePath))
                {
                    textureAtlas.addTexture(utl::asString(tileData.first), "Media/Image/Game/Tiles/Debug/Missing.png");
                    std::cout << "TILEENGINE - Tile: '" << texturePath << "' failed to load <Utl/SaveFile/SaveFile_TileEngine.cpp>" << std::endl;
                }
            }
            else
            {
                std::cout << "TILEENGINE - Tile extension: '" << filePath << "' is not accepted <Utl/SaveFile/SaveFile_TileEngine.cpp>" << std::endl;
                textureAtlas.addTexture(utl::asString(tileData.first), "Media/Image/Game/Tiles/Debug/Missing.png");
            }
        }
        //now texture exists in resourceManager, compiledTexture only holds a pointer to the texture
        compiledTexture = textureAtlas.compileTextures("TILESTORAGE");
    }

    //gets tileTransform data
    for(auto& tileData : tileLocations)
    {
        const int& tileID = tileData.first;
        const std::string& filePath = tileData.second;

        if(filePath.substr(filePath.length() - 4) == ".png")
        {
            TileTransform tile = TileTransform(filePath);
            tile.tileSize = utl::Vector2i(1,2);
            tileTransform.emplace(std::make_pair(tileID, tile));
        }
        else if(filePath.substr(filePath.length() - 4) == ".txt")
        {
            //TODO implement .txt in Tile Editor
            std::string texturePath = filePath;
            texturePath.resize(texturePath.length() - 4);
            texturePath = utl::conjoinString({texturePath,".png"});

            TileTransform tile = TileTransform(texturePath);
            tile.tileSize = utl::Vector2i(1,1);

            tileTransform.emplace(std::make_pair(tileID, TileTransform(texturePath)));
        }
        else
        {
            std::cout << "TILEENGINE - Tile extension: '" << filePath << "' is not accepted <Utl/SaveFile/SaveFile_TileEngine.cpp>" << std::endl;
            textureAtlas.addTexture(utl::asString(tileData.first), "Media/Image/Game/Tiles/Debug/Missing.png");
        }
    }

    //load tileInfo into mapData
    for(auto& tileData : tileLocations)
    {
        const int& tileID = tileData.first;

        std::string& texturePath = tileTransform.at(tileID).texturePath;
        utl::Vector2i& tileSize  = tileTransform.at(tileID).tileSize;
        int& degrees             = tileTransform.at(tileID).degrees;
        char& flip               = tileTransform.at(tileID).flip;

        mapData.tileStorage.emplace(tileID, Tile(window, resourceManager));

        switch (tileMode)
        {
        case TileMode::Batch:
        {
            mapData.tileStorage.at(tileID).tileType = Tile::TileType::texture;
            mapData.tileStorage.at(tileID).texturePosition = compiledTexture.textureCoords.at(utl::asString(tileID));
        }
        break;
        case TileMode::Sprite:
        {
            mapData.tileStorage.at(tileID).tileType = Tile::TileType::sprite;
            mapData.tileStorage.at(tileID).setTexture(texturePath);
        }
        break;
        }
        mapData.tileStorage.at(tileID).setSize(tileSize.x,tileSize.y);
        mapData.tileStorage.at(tileID).setRotate(degrees);
        mapData.tileStorage.at(tileID).setFlip(flip);
    }
    /*
        mapData.tileStorage.emplace(1, Tile(window, resourceManager));
        mapData.tileStorage.at(1).texturePosition = compiledTexture.textureCoords.at("1");
        mapData.tileStorage.at(1).setSize(1,1);
        //temp, only for tileEditor
        //mapData.tileStorage.at(std::make_pair(1,1)).tileType = Tile::TileType::sprite;
        mapData.tileStorage.at(1).setTexture("Media/Image/Game/Tiles/01/01.png");
        mapData.tileStorage.at(1).setSize(1,1);


        mapData.tileStorage.emplace(22, Tile(window, resourceManager));
        mapData.tileStorage.at(22).texturePosition = compiledTexture.textureCoords.at("22");
        mapData.tileStorage.at(22).setSize(1,1);
        //temp, only for tileEditor
        mapData.tileStorage.at(22).tileType = Tile::TileType::sprite;
        mapData.tileStorage.at(22).setTexture("Media/Image/Game/Tiles/04/21.png");
        mapData.tileStorage.at(22).setSize(1,1);

        //////////////TEST
        mapData.tileStorage.emplace(7, Tile(window, resourceManager));
        mapData.tileStorage.at(7).texturePosition = compiledTexture.textureCoords.at("3");
        //mapData.tileStorage.at(std::make_pair(7,7)).setSize(1,1);
        //mapData.tileStorage.at(std::make_pair(7,7)).setRotate(90);
        //mapData.tileStorage.at(std::make_pair(7,7)).setFlip('b');
        //temp, only for tileEditor
        mapData.tileStorage.at(7).tileType = Tile::TileType::sprite;
        mapData.tileStorage.at(7).setTexture("Media/Image/Game/Tiles/TESTING/Arrow.png");
        mapData.tileStorage.at(7).setSize(1,1);
        //mapData.tileStorage.at(std::make_pair(7,7)).setRotate(90);
        mapData.tileStorage.at(7).setFlip('b');
        //////////////TEST

        mapData.tileStorage.emplace(3, Tile(window, resourceManager));
        mapData.tileStorage.at(3).texturePosition = compiledTexture.textureCoords.at("4");
        mapData.tileStorage.at(3).setSize(1,1);

        mapData.tileStorage.emplace(75, Tile(window, resourceManager));
        mapData.tileStorage.at(75).setTexture("Media/Image/Game/Tiles/75/01.png");
        mapData.tileStorage.at(75).setSize(1,1);
        */
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
    //temp
    saveFile_tilesUsed.addItem("nil", "nil");
    saveFile_tilesUsed.writeFile();

    //create map save
    SaveFile saveFile_map;
    saveFile_map.setFilePath(filePath + file_map);
    //get the map string
    const std::string nullTile  =    "0|";
    const std::string nullTileEnd  = "0";
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
