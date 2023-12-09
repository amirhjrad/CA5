#include "game.h"
#include "constants.h"

void Game::removeCollectedKeys()
{
    keys.erase(remove_if(keys.begin(), keys.end(), []( Key& key) 
    {
        return key.isRemovable();
    }), keys.end());    
}

void Game::removePU()
{
    PUs.erase(std::remove_if(PUs.begin(), PUs.end(), [](PowerUp& PU) {
        return PU.isRemovable();
    }), PUs.end());
}

void Game::removeEnemy()
{
    enemies.erase(remove_if(enemies.begin(), enemies.end(), []( Enemy& enemy) 
    {
        return enemy.isRemovable();
    }), enemies.end());    
}

void Game::doublePlayerSpeed()
{
    PLAYER_SPEED *= 2;
}

void Game::handleKeyreveal()
{
    int numOfKeys = NUM_OF_KEY;
    for(int i = 0; i < numOfKeys; i++)
    {
        int x = keys[i].getPosition().x / KEYS_SIZE;
        int y = keys[i].getPosition().y / KEYS_SIZE;
        if(x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT)
        {
            if(map[y][x] == NOTHING)
            {
                revealedKeys += 1;
                keys[i].shouldReveal();
            }
        }
    }
}

void Game::handlePUReveal()
    {
        int numOfPU = NUM_OF_PU;
        for(int i = 0; i < numOfPU; i++)
        {
            int x = PUs[i].getPosition().x / PU_SIZE;
            int y = PUs[i].getPosition().y / PU_SIZE;
            if(x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT)
            {
                if(map[y][x] == NOTHING)
                {
                    revealedPUs += 1;
                
                    PUs[i].shouldReveal();
                }
            }  
        }        
    }

void Game::removeSoftObstaclesAroundBomb(const sf::Vector2f& bombPosition)
{
    int bombGridX = static_cast<int>(bombPosition.x) / SOFT_OBS_SIZE;
    int bombGridY = static_cast<int>(bombPosition.y) / SOFT_OBS_SIZE;
    int radius = 1; 
    
    if (bombGridY - radius >= 0 && map[bombGridY - radius][bombGridX] == IM_DOOR)  
        map[bombGridY - radius][bombGridX] = REAL_DOOR;

    if (bombGridY + radius < static_cast<int>(map.size()) && map[bombGridY + radius][bombGridX] == IM_DOOR)
        map[bombGridY + radius][bombGridX] = REAL_DOOR;

    if (bombGridX - radius >= 0 && map[bombGridY][bombGridX - radius] == IM_DOOR)
        map[bombGridY][bombGridX - radius] = REAL_DOOR;

    if (bombGridX + radius < static_cast<int>(map[bombGridY].size()) && map[bombGridY][bombGridX + radius] == IM_DOOR)
        map[bombGridY][bombGridX + radius] = REAL_DOOR;

    if (bombGridY - radius >= 0 && map[bombGridY - radius][bombGridX] == SOFT_OBS)
        map[bombGridY - radius][bombGridX] = NOTHING;

    if (bombGridY + radius < static_cast<int>(map.size()) && map[bombGridY + radius][bombGridX] == SOFT_OBS)
        map[bombGridY + radius][bombGridX] = NOTHING;

    if (bombGridX - radius >= 0 && map[bombGridY][bombGridX - radius] == SOFT_OBS)
        map[bombGridY][bombGridX - radius] = NOTHING;

    if (bombGridX + radius < static_cast<int>(map[bombGridY].size()) && map[bombGridY][bombGridX + radius] == SOFT_OBS)
        map[bombGridY][bombGridX + radius] = NOTHING;
}

void Game::placeKey()
{
    std::vector<std::pair<int, int>> wallPositions;
    for (int i = 0; i < static_cast<int>(map.size()); ++i) 
    {
        for (int j = 0; j < static_cast<int>(map[i].size()); ++j) 
        {
            if (map[i][j] == SOFT_OBS) 
            {
                wallPositions.push_back(std::make_pair(i, j));
            }
        }
    }
    std::random_device rd;
    std::mt19937 gen(rd());
    shuffle(wallPositions.begin(), wallPositions.end(), gen);
    std::uniform_int_distribution<int> dist(0, wallPositions.size() - 1);
    int randomIndex = dist(gen);
    std::pair<int, int> keyPosition = wallPositions[randomIndex];
    sf::Vector2f keyPositionSF(keyPosition.second * KEYS_SIZE, keyPosition.first * KEYS_SIZE);
    tmpKey.setPosition(keyPositionSF);
    if (keys.size() == 0)
    {
        keys.push_back(tmpKey);
    }
    else
    {
        for(int i = 0; i < static_cast<int>(keys.size()); i++)
        {
            if(keys[i].getPosition() == tmpKey.getPosition())
            {
                placeKey();
            }
        }
        keys.push_back(tmpKey);       
    }
}

void Game::placePU()
{
    std::vector<std::pair<int, int>> wallPositions;
    for (int i = 0; i < static_cast<int>(map.size()); ++i) 
    {
        for (int j = 0; j < static_cast<int>(map[i].size()); ++j) 
        {
            if (map[i][j] == SOFT_OBS) 
            {
                wallPositions.push_back(std::make_pair(i, j));
            }
        }
    }
    std::random_device rd;
    std::mt19937 gen(rd());
    shuffle(wallPositions.begin(), wallPositions.end(), gen);
    std::uniform_int_distribution<int> dist(0, wallPositions.size() - 1);
    int randomIndex = dist(gen);
    std::pair<int, int> PUPosition = wallPositions[randomIndex];
    sf::Vector2f PUPositionSF(PUPosition.second * PU_SIZE, PUPosition.first * PU_SIZE);
    tmpPU.setPosition(PUPositionSF);
    
    bool foundValidPosition = false;
    while (!foundValidPosition)
    {
        bool positionValid = true;
        for (int i = 0; i < static_cast<int>(PUs.size()); i++)
        {
            if (PUs[i].getPosition() == tmpPU.getPosition())
            {
                positionValid = false;
                break;
            }
        }
        for (int j = 0; j < NUM_OF_KEY; j++)
        {
            if (keys[j].getPosition() == tmpPU.getPosition())
            {
                positionValid = false;
                break;
            }
        }
        if (positionValid)
        {
            foundValidPosition = true;
        }
        else
        {
            randomIndex = dist(gen);
            PUPosition = wallPositions[randomIndex];
            PUPositionSF = sf::Vector2f(PUPosition.second * PU_SIZE, PUPosition.first * PU_SIZE);
            tmpPU.setPosition(PUPositionSF);
        }
    }
    
    PUs.push_back(tmpPU);
}


void Game::removeExpiredBombs()
{
    bombs.erase(remove_if(bombs.begin(), bombs.end(), []( Bomb& bomb) 
    {
        return bomb.remove();
    }), bombs.end());
}

void Game::drawTexture()
{
    int numTilesX = window.getSize().x / 50;
    int numTilesY = window.getSize().y / 50;
    for (int i = 0; i < numTilesX; ++i) 
    {
        for (int j = 0; j < numTilesY; ++j) 
        {
            if (map[j][i] == NOTHING || map[j][i] == REAL_DOOR) 
            {
                grass.setPosition(sf::Vector2f(i * GRASS_SIZE, j * GRASS_SIZE));
                grass.draw(window);
            }
        }
    }
    int numRows = map.size();
    int numCols = (numRows > 0) ? map[0].size() : 0;
    for (int i = 0; i < numRows; ++i)
    {
        for (int j = 0; j < numCols; ++j)
        {
            char c = map[i][j];
            sf::Vector2f position(j * 50, i * 50);
            if (c == SOFT_OBS)
            {
                SoftObstacle obs;
                obs.setPosition(position);
                obs.draw(window);
            }
            else if (c == HARD_OBS)
            {
                HardObstacle obs;
                obs.setPosition(position);
                obs.draw(window);
            }
            else if(c == VERTICAL_ENEMY)
            {
                tmpEnemy.setPosition(position);
                tmpEnemy.isVertical = true;
                enemies.push_back(tmpEnemy);
                map[i][j] = NOTHING;
            }
            else if(c == HORIZONTAL_ENEMY)
            {
                tmpEnemy.setPosition(position);
                tmpEnemy.isVertical = false;
                enemies.push_back(tmpEnemy);
                map[i][j] = NOTHING;
            }
            else if(c == IM_DOOR)
            {
                SoftObstacle obs;
                obs.setPosition(position);
                obs.draw(window);
                door.setPosition(position);
            }
            else if(c == REAL_DOOR)
            {
                door.setPosition(position);
                door.draw(window);
            }

        }
    }
}

void Game::EndGame() 
{
    window.clear();
    sf::Font font;
    font.loadFromFile(FONT_DIR);
    sf::Text message;
    if(gameTimer == TIME_FINISHED)
        message.setString(TIME_FINISHED_LABEL);
    else 
        message.setString(LIFE_FINISHED_LABEL);
    message.setFont(font);
    message.setCharacterSize(FONT_SIZE);
    message.setFillColor(sf::Color::White);
    message.setPosition(WINDOW_WIDTH/2.5, WINDOW_HEIGHT/2.5);
    window.draw(message);
    window.display();
}

void Game::Win()
{
    window.clear();
    sf::Font font;
    font.loadFromFile(FONT_DIR);
    sf::Text message;
    message.setString(WIN_LABEL);
    message.setFont(font);
    message.setCharacterSize(FONT_SIZE);
    message.setFillColor(sf::Color::White);
    message.setPosition(WINDOW_WIDTH/2.5, WINDOW_HEIGHT/2.5);
    window.draw(message);
    window.display();
}

void Game::run() 
{
    sf::Clock clock;
    initial();
    while (window.isOpen())
    {
        sf::Time deltaTime = clock.restart();
        processEvents(deltaTime);
        update(deltaTime);
        render();
    }
}

void Game::handleEnemyMovement(Enemy& enemy)
{
    sf::Vector2f movement(0.0f, 0.0f);
    if (enemy.isVertical) 
    {
        if (enemy.upOrRight) 
            movement.y -= ENEMY_SPEED;
        else movement.y += ENEMY_SPEED;
    }
    else 
    {
        if (enemy.upOrRight) 
            movement.x += ENEMY_SPEED;
        else movement.x -= ENEMY_SPEED;
    }
    sf::FloatRect enemyBounds = enemy.getBounds();
    int x = static_cast<int>((enemyBounds.left)/ ENEMY_SIZE);
    int y = static_cast<int>((enemyBounds.top) / ENEMY_SIZE);
    if (x < 1 || x + 1 > static_cast<int>(map[0].size())|| y < 1 || y + 1 >= static_cast<int>(map.size())) 
    {
        enemy.upOrRight = !enemy.upOrRight;
        movement = -movement;
        enemy.move(movement);
        return;
    }
    else if (map[y + 1][x] == SOFT_OBS || map[y + 1][x] == HARD_OBS || map[y + 1][x] == IM_DOOR) 
    {
            if (enemy.isVertical) 
            {
                enemy.upOrRight = !enemy.upOrRight;
                movement.y = -movement.y;
            }
    }
    else if(map[y][x] == SOFT_OBS || map[y][x] == HARD_OBS || map[y][x] == IM_DOOR)
    {
            if (enemy.isVertical) 
            {
                enemy.upOrRight = !enemy.upOrRight;
                movement.y = -movement.y;
            } 
            else
            {
                enemy.upOrRight = !enemy.upOrRight;
                movement.x = -movement.x;                
            }      
    }
    else if(map[y][x + 1] == SOFT_OBS || map[y][x + 1] == HARD_OBS || map[y][x + 1] == IM_DOOR)
    {
        if(!enemy.isVertical)
        {
            enemy.upOrRight = !enemy.upOrRight;
            movement.x = -movement.x;
        }
    }
    enemy.move(movement);
}

void Game::handlePlayerMovement(sf::Time deltaTime)
{
    sf::Vector2f movement(0.0f, 0.0f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        movement.y -= PLAYER_SPEED * deltaTime.asSeconds();
        player.setTexture(UP);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        movement.y += PLAYER_SPEED * deltaTime.asSeconds();
        player.setTexture(DOWN);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        movement.x -= PLAYER_SPEED * deltaTime.asSeconds();
        player.setTexture(LEFT);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        movement.x += PLAYER_SPEED * deltaTime.asSeconds();
        player.setTexture(RIGHT);
    }
    sf::Vector2f newPosition = player.getPosition() + movement;
    sf::FloatRect enemyBounds = player.getBounds();
    sf::FloatRect windowBounds(0.0f, 50.0f - 6, WINDOW_WIDTH, WINDOW_HEIGHT - 50.0f);
    sf::FloatRect newBounds(newPosition, sf::Vector2f(enemyBounds.width, enemyBounds.height));
    bool obstacleCollision = false;
    for (int i = 0; i < static_cast<int>(map.size()); ++i)
    {
        for (int j = 0; j < static_cast<int>(map[i].size()); ++j)
        {
            char c = map[i][j];
            sf::Vector2f obstaclePosition(j * SOFT_OBS_SIZE, i * SOFT_OBS_SIZE);
            sf::FloatRect obstacleBounds(obstaclePosition, sf::Vector2f(40.0f, 40.0f));
            if (c == SOFT_OBS || c == HARD_OBS || c == IM_DOOR)
            {
                if (newBounds.intersects(obstacleBounds))
                {
                    obstacleCollision = true;
                    break;
                }
            }
        }
    }
    if (!obstacleCollision && windowBounds.contains(newPosition) &&
        windowBounds.contains(newPosition + sf::Vector2f(enemyBounds.width, enemyBounds.height)))
    {   
        player.move(movement);
    }
}

void Game::handleBombPlacement()
{
        if(player.getNumOfBombs() < MAX_BOMB)
        {
            sf::Vector2f playerPosition = player.getPosition();
            int gridX = static_cast<int>(playerPosition.x + player.getBounds().width / 2) / BOMB_SIZE;
            int gridY = static_cast<int>(playerPosition.y + player.getBounds().height / 2) / BOMB_SIZE;
            float positionX = (gridX * BOMB_SIZE);
            float positionY = (gridY * BOMB_SIZE);
            if (gridX >= 0 && gridX < (WINDOW_WIDTH / BOMB_SIZE) && gridY >= 0 && gridY < (WINDOW_HEIGHT / BOMB_SIZE))
            {
                tmpBomb.setPosition(sf::Vector2f(positionX, positionY));
                bombs.push_back(tmpBomb);
            }
            player.incNumOfBombs();
        }
}

void Game::readMapFile(const std::string& filename)
{
    std::ifstream file(filename);
    std::string line;
    int first = 1;
    while (getline(file, line))
    {
        std::vector<char> row;
        if(!first)
        {
            for (char c : line)
            {
                row.push_back(c);
            }
        }
        else {
            for (int j=0 ; j< WINDOW_WIDTH/50; j++)
                row.push_back('.');
            first = 0;
            gameTimer = stoi(line);
        }
        map.push_back(row);
            
    }
    file.close();
    for(int i = 0; i < NUM_OF_KEY; i++)
        placeKey();
    for(int i = 0; i < NUM_OF_PU; i++)
    {
        placePU();
        if(i == 0)
            PUs[i].tmp = 0;
        if(i == 1)
            PUs[i].tmp = 1;
    }
}

void Game::drawInfoBoard() 
{
    sf::RectangleShape livesSection(sf::Vector2f(WINDOW_WIDTH, 50));
    livesSection.setFillColor(sf::Color(128,128,128));
    window.draw(livesSection);
    sf::Font font;
    font.loadFromFile(FONT_DIR);
    sf::Text livesText(LIVES_LABEL + std::to_string(player.getLives()), font, 20);
    livesText.setFillColor(sf::Color::White);
    livesText.setPosition(10, 10);
    sf::RectangleShape keysSection(sf::Vector2f(WINDOW_WIDTH, 50));
    keysSection.setFillColor(sf::Color(128,128,128));
    window.draw(keysSection);
    sf::Text keysText(KEYS_LABEL + std::to_string(player.getNumOfCollectedKeys()), font, 20);
    keysText.setFillColor(sf::Color::White);
    keysText.setPosition(100, 10);
    window.draw(livesText); 
    window.draw(keysText); 
    std::chrono::duration<double> countDownDuration(gameTimer); 
    std::chrono::duration<double> elapsedTime = std::chrono::system_clock::now() - startTime;
    std::chrono::duration<double> remainingTime = countDownDuration - elapsedTime;
    if(remainingTime.count() > 0)
    {
        int remainingSeconds = static_cast<int>(remainingTime.count());
        sf::Text countdownText(TIMER_LABEL + std::to_string(remainingSeconds), font, 20);
        countdownText.setFillColor(sf::Color::White);
        countdownText.setPosition(200, 10);
        window.draw(countdownText);
    }
    else gameTimer = -1;
}

void Game::initial()
{
    PLAYER_SPEED = 200;
    startTime = std::chrono::system_clock::now();
    readMapFile(MAP_DIR);
}

void Game::processEvents(sf::Time deltaTime)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();
        if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::X)
            handleBombPlacement();
    }
}

void Game::update(sf::Time deltaTime)
{
    if(player.playerOnDoor(door))
    {
        finished = true;
        Win();
    }
    else if(player.getLives() <= 0 || gameTimer == TIME_FINISHED)
    {
        EndGame();
        finished = true;
    }
    handlePlayerMovement(deltaTime);
    for(Enemy &enemy : enemies)
    {
        handleEnemyMovement(enemy);
    }
    float lastTimeCalled;
    for (Enemy& enemy : enemies)
    {
        float timePassed = clock.getElapsedTime().asSeconds();
        lastTimeCalled = timePassed + 0.5;
        if (lastTimeCalled < 2)
            continue;

        if (player.playerOnEnemy(enemy))
        {
            lastTimeCalled = 0;
            clock.restart();
            player.decLives();
        }
    }
    for (Bomb& bomb : bombs) 
    {
        bomb.update(deltaTime);
        if (bomb.remove()) 
        {
            player.decNumOfBombs();
            removeSoftObstaclesAroundBomb(bomb.getPosition());
            if(player.playerOnBomb(bomb)) 
            {
                player.decLives();
            }
            for(Enemy &enemy : enemies)
            {
                if(enemy.enemyOnBomb(bomb))
                    enemy.shouldRemove();
            }
        }
    }
    removeEnemy();
    removeExpiredBombs();
    handleKeyreveal();
    handlePUReveal();
    for(PowerUp& powerUp : PUs)
    {
        if(powerUp.isRevealed())
        {
            if(player.playerOnPU(powerUp))
            {
                powerUp.shouldRemove();
                if(powerUp.tmp == 0)
                {
                    if(player.getLives() < INIT_LIVES +1)
                        player.incLive();
                }
                if(powerUp.tmp == 1)
                    doublePlayerSpeed();
            }
        }
    }
    removePU(); 
    for (Key& key : keys) 
    {
        if(key.isRevealed())
        {
            if(player.playerOnKey(key)) 
            {
                player.collectKey();
                key.shouldRemove();
            }
        }
    }
    removeCollectedKeys();
}

void Game::render()
{
    window.clear();
    drawTexture();
    player.draw(window);
    for(Bomb &tmpBomb : bombs)
    {
        tmpBomb.draw(window);
    }
    for(Key &tmpKey : keys)
    {
        if(tmpKey.isRevealed())
        {
            tmpKey.draw(window);
        }
    }

    for(PowerUp &tmpPU : PUs)
    {
        if(tmpPU.isRevealed())
        {
            tmpPU.setTexture(tmpPU.tmp);
            tmpPU.draw(window);
        }
    }
    for(Enemy &tmpEnemy : enemies)
    {
        tmpEnemy.draw(window);
    }
    drawInfoBoard();
    if(!finished)
        window.display();
}