#include "Game.h"

void Game::character_selection_menu(sf::RenderWindow& window)
{
    char_select.select_class_menu(window);
    player.set_class(char_select.get_class());
    set_interface();
}

state_of_game Game::play_level(sf::RenderWindow& window, std::string& level_filename)
{
    window.setFramerateLimit(120);
    Level level;
    if (!level.load_tilemap(level_filename) || !level.load_player())
        return state_of_game::file_error;

    set_level(&level);
    set_playerpos();
    player.reset_spawn_timer();
    sf::Vector2i MousePosition;
    sf::Vector2f target;
    sf::Event event;
    clock.restart().asSeconds();

    while (window.isOpen())
    {
        MousePosition = sf::Mouse::getPosition(window);
        target = window.mapPixelToCoords(MousePosition) + player_view.getCenter() - view_size / 2.f;

        deltaTime = clock.restart().asSeconds();
        game_time += deltaTime;

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            player.primary_attack(target);

        if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
        {
            if (player.get_class() == character_class::wizard)
            {
                if (player.get_mana() < player.get_max_mana())
                    player.secondary_attack(target);
            }
            else
                player.secondary_attack(target);
        }

        if (player.get_mana() >= 1)
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num1))
                player.first_spell(target);

            if (player.get_mana() >= 2)
            {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num2))
                {
                    if (player.get_class() == character_class::wizard)
                        player.second_spell(target);
                    else if (player.get_hit_points() < player.get_max_hit_points())
                        player.second_spell(target);
                }

                if (player.get_class() == character_class::wizard)
                {
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num3))
                        player.third_spell(target);

                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num4))
                        if (player.get_hit_points() < player.get_max_hit_points())
                            player.fourth_spell();
                }
            }
        }

        if (player.get_mana_regen_timer().getElapsedTime().asSeconds() >= 10.f)
        {
            if (player.get_mana() < player.get_max_mana())
                player.add_mana();
            player.reset_mana_regen_timer();
        }

        if (player.is_mana_regen())
            mana_text.setFillColor(sf::Color(112, 248, 255));

        if (mana_text.getFillColor() == sf::Color(112, 248, 255))
            if (!player.is_mana_regen())
                mana_text.setFillColor(sf::Color(3, 177, 252));

        if (player.is_healed())
            hp_text.setFillColor(sf::Color(255, 105, 105));

        if (hp_text.getFillColor() == sf::Color(255, 105, 105))
            if (!player.is_healed())
                hp_text.setFillColor(sf::Color(255, 26, 26));

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Escape)
                    if (!pause_game(window))
                        return state_of_game::lost;
            }
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            if (target.x >= options[0].getGlobalBounds().left + player_view.getCenter().x - view_size.x / 2.f &&
                target.x <= options[0].getGlobalBounds().left + options[0].getGlobalBounds().width + player_view.getCenter().x - view_size.x / 2.f &&
                target.y >= options[0].getGlobalBounds().top + player_view.getCenter().y - view_size.y / 2.f &&
                target.y <= options[0].getGlobalBounds().top + options[0].getGlobalBounds().height + player_view.getCenter().y - view_size.y / 2.f)
                spellbook(window);

            if (target.x >= options[1].getGlobalBounds().left + player_view.getCenter().x - view_size.x / 2.f &&
                target.x <= options[1].getGlobalBounds().left + options[1].getGlobalBounds().width + player_view.getCenter().x - view_size.x / 2.f &&
                target.y >= options[1].getGlobalBounds().top + player_view.getCenter().y - view_size.y / 2.f &&
                target.y <= options[1].getGlobalBounds().top + options[1].getGlobalBounds().height + player_view.getCenter().y - view_size.y / 2.f)
                equipment(window);

            if (target.x >= options[2].getGlobalBounds().left + player_view.getCenter().x - view_size.x / 2.f &&
                target.x <= options[2].getGlobalBounds().left + options[2].getGlobalBounds().width + player_view.getCenter().x - view_size.x / 2.f &&
                target.y >= options[2].getGlobalBounds().top + player_view.getCenter().y - view_size.y / 2.f &&
                target.y <= options[2].getGlobalBounds().top + options[2].getGlobalBounds().height + player_view.getCenter().y - view_size.y / 2.f)
                if (!pause_game(window))
                    return state_of_game::lost;
        }

        update_player(window);
        move_enemies(window);
        update_player_projectiles();
        update_enemy_projectiles();

        window.clear();
        window.setView(player_view);
        window.draw(game_background);
        level.draw_level(window);
        draw_player_projectiles(window);
        draw_enemy_projectiles(window);
        window.draw(player);
        window.setView(user_interface);
        draw_interface(window);
        window.display();

        if (player.get_completed())
        {
            player.set_completed(false);
            return state_of_game::completed_level;
        }
        else if (player.get_hit_points() <= 0)
            return state_of_game::lost;
    }
    return state_of_game::error;
}

void Game::set_view()
{
    if (player.get_position().x + player.get_size().x / 2 < view_size.x / 2 && player.get_position().y + player.get_size().y / 2 < view_size.y / 2)
        player_view.setCenter(sf::Vector2f(view_size.x / 2, view_size.y / 2));

    else if (player.get_position().x + player.get_size().x / 2 < view_size.x / 2)
        player_view.setCenter(sf::Vector2f(view_size.x / 2, player.get_position().y + player.get_size().y / 2));

    else if (player.get_position().y + player.get_size().y / 2 < view_size.y / 2)
        player_view.setCenter(sf::Vector2f(player.get_position().x + player.get_size().x / 2, view_size.y / 2));

    else
        player_view.setCenter(player.get_position() + sf::Vector2f(player.get_size().x / 2, player.get_size().y / 2));
}

void Game::move_enemies(sf::RenderWindow& window)
{
    std::vector<std::unique_ptr<Unit>>::const_iterator unit_iter;
    for (unit_iter = level->get_enemies().begin(); unit_iter != level->get_enemies().end(); ++unit_iter)
    {
        (*unit_iter)->update_unit(deltaTime, window, &player);
        level->check_collision_vertical((*unit_iter).get());
        level->check_collision_horizontal((*unit_iter).get());

        if ((*unit_iter)->get_position().y > level->get_height() * 32.f + 200.f)
        {
            unit_iter = level->get_enemies().erase(unit_iter);
        }
    }
}

void Game::update_player(sf::RenderWindow& window)
{
    player.update_unit(deltaTime, window);
    level->check_collision_horizontal(&player);
    level->check_collision_vertical(&player);
    level->check_for_pickups(player);

    std::vector<std::unique_ptr<Unit>>::const_iterator unit_iter;
    for (unit_iter = level->get_enemies().begin(); unit_iter != level->get_enemies().end(); ++unit_iter)
        (*unit_iter)->set_player_position(player.get_position().x, player.get_position().y);

    set_view();
}

void Game::update_player_projectiles()
{
    std::vector<std::unique_ptr<Projectile>>::const_iterator iter;
    for (iter = player.get_projectile()->begin(); iter != player.get_projectile()->end();)
    {
        if (check_if_hit_enemy((*iter).get()))
            iter = player.get_projectile()->erase(iter);
        else ++iter;
    }
}

void Game::update_enemy_projectiles()
{
    std::vector<std::unique_ptr<Unit>>::const_iterator iter;
    std::vector<std::unique_ptr<Projectile>>::const_iterator arrow_iter;
    for (iter = level->get_enemies().begin(); iter != level->get_enemies().end(); ++iter)
    {
        if ((*iter)->get_projectile() != nullptr)
        {
            for (arrow_iter = (*iter)->get_projectile()->begin(); arrow_iter != (*iter)->get_projectile()->end();)
            {
                if (check_if_hit_player((*arrow_iter).get()))
                    arrow_iter = (*iter)->get_projectile()->erase(arrow_iter);
                else ++arrow_iter;
            }
        }
    }
}

bool Game::check_if_hit_enemy(Projectile* projectile)
{
    projectile->move_projectile(deltaTime);
    int x = int(projectile->get_position().x / 32.f);
    int y = int(projectile->get_position().y / 32.f);
    if (projectile->get_type() != projectile_type::melee &&
        projectile->get_type() != projectile_type::stun &&
        projectile->get_type() != projectile_type::lightning)
    {
        for (int i = y - 1; i <= y + 1; i++)
        {
            for (int j = x - 1; j <= x + 1; j++)
            {
                if (level->get_tilemap()[std::make_pair(i, j)] != nullptr && level->get_tilemap()[std::make_pair(i, j)].get()->get_name() != tile_type::floor)
                    if (projectile->get_projectile().getGlobalBounds().intersects(level->get_tilemap()[std::make_pair(i, j)]->get_tile().getGlobalBounds()))
                        return true;
            }
        }
    }
    if ((!projectile->did_hit()) &&
        (projectile->get_type() == projectile_type::melee ||
         projectile->get_type() == projectile_type::stun ||
         projectile->get_type() == projectile_type::lightning) ||
        (projectile->get_type() != projectile_type::melee &&
         projectile->get_type() != projectile_type::lightning &&
         projectile->get_type() != projectile_type::stun))
    {
        std::vector<std::unique_ptr<Unit>>::const_iterator unit_iter = level->get_enemies().begin();
        while (unit_iter != level->get_enemies().end())
        {
            float left = projectile->get_projectile().getGlobalBounds().left;
            float top = projectile->get_projectile().getGlobalBounds().top;
            float width = projectile->get_projectile().getGlobalBounds().width;
            float height = projectile->get_projectile().getGlobalBounds().height;
            if (projectile->get_type() == projectile_type::lightning)
            {
                left = projectile->get_projectile().getGlobalBounds().left + (projectile->get_projectile().getGlobalBounds().width) / 2.f - 1.f;
                top = projectile->get_projectile().getGlobalBounds().top + projectile->get_projectile().getGlobalBounds().height;
                width = 2.f;
                height = 1.f;
            }
            sf::Rect projectile_rect(left, top, width, height);
            if (projectile_rect.intersects((*unit_iter)->get_unit().getGlobalBounds()))
            {
                if (projectile->get_type() == projectile_type::flurry)
                    (*unit_iter)->slow_down();
                if (projectile->get_type() == projectile_type::stun)
                    (*unit_iter)->stun();
                (*unit_iter)->damage(projectile->get_damage());
                if ((*unit_iter)->get_hit_points() <= 0)
                {
                    player.add_points((*unit_iter)->get_points_worth());
                    player.add_exp((*unit_iter)->get_experience_worth());
                    level->get_enemies().erase(unit_iter);
                }
                projectile->set_hit(true);
                break;
            }
            ++unit_iter;
        }
    }
    if (projectile->did_hit() &&
       (projectile->get_type() != projectile_type::melee &&
        projectile->get_type() != projectile_type::stun &&
        projectile->get_type() != projectile_type::lightning))
        return true;
    if (projectile->get_flown_distance() > projectile->get_range())
        return true;
    return false;
}

bool Game::check_if_hit_player(Projectile* projectile)
{
    projectile->move_projectile(deltaTime);
    int x = int(projectile->get_position().x / 32.f);
    int y = int(projectile->get_position().y / 32.f);
    if (projectile->get_type() != projectile_type::melee)
    {
        for (int i = y - 1; i <= y + 1; i++)
        {
            for (int j = x - 1; j <= x + 1; j++)
            {
                if (level->get_tilemap()[std::make_pair(i, j)] != nullptr && level->get_tilemap()[std::make_pair(i, j)].get()->get_name() != tile_type::floor)
                    if (projectile->get_projectile().getGlobalBounds().intersects(level->get_tilemap()[std::make_pair(i, j)]->get_tile().getGlobalBounds()))
                        return true;
            }
        }
    }
    if ((projectile->get_type() == projectile_type::melee && !projectile->did_hit()) || projectile->get_type() != projectile_type::melee)
    {
        if (projectile->get_projectile().getGlobalBounds().intersects(player.get_unit().getGlobalBounds()))
        {
            player.damage(projectile->get_damage());
            projectile->set_hit(true);
        }
    }
    if (projectile->did_hit() && projectile->get_type() != projectile_type::melee)
        return true;
    if (projectile->get_flown_distance() > projectile->get_range())
        return true;
    return false;
}

void Game::set_playerpos()
{
    player.set_player_shape();
    player.set_position(sf::Vector2f(level->get_player_spawn()));
    player.set_spawn_position(sf::Vector2f(level->get_player_spawn()));
}

void Game::draw_player_projectiles(sf::RenderWindow& window)
{
    std::vector<std::unique_ptr<Projectile>>::const_iterator iter;
    for (iter = player.get_projectile()->begin(); iter != player.get_projectile()->end(); ++iter)
        window.draw((*iter)->get_projectile());
}

void Game::draw_enemy_projectiles(sf::RenderWindow& window)
{
    std::vector<std::unique_ptr<Unit>>::const_iterator iter;
    std::vector<std::unique_ptr<Projectile>>::const_iterator bullet_iter;
    for (iter = level->get_enemies().begin(); iter != level->get_enemies().end(); ++iter)
    {
        if ((*iter)->get_projectile() != nullptr)
        {
            for (bullet_iter = (*iter)->get_projectile()->begin(); bullet_iter != (*iter)->get_projectile()->end(); ++bullet_iter)
                window.draw((*bullet_iter)->get_projectile());
        }
    }
}

void Game::draw_interface(sf::RenderWindow& window)
{
    name_text.setPosition((view_size.x - name_text.getGlobalBounds().width) / 2 - 174.f, view_size.y - 45.f);

    class_text.setPosition((view_size.x - class_text.getGlobalBounds().width) / 2 - 174.f, view_size.y - 35.f);

    lvl_text.setString("POZIOM: " + std::to_string(player.get_level()));
    lvl_text.setPosition((view_size.x - lvl_text.getGlobalBounds().width) / 2 - 174.f, view_size.y - 23.f);

    exp_text.setString("EXP: " + std::to_string(player.get_experience()) + "/" + std::to_string(player.get_required_exp()));
    exp_text.setPosition((view_size.x - exp_text.getGlobalBounds().width) / 2 - 174.f, view_size.y - 14.f);

    hp_text.setString("ZYCIE: " + std::to_string(player.get_hit_points()) + "/" + std::to_string(player.get_max_hit_points()));
    hp_text.setPosition((view_size.x - hp_text.getGlobalBounds().width) / 2 - 80.f, view_size.y - 47.f);

    mana_text.setString("MANA: " + std::to_string(player.get_mana()) + "/" + std::to_string(player.get_max_mana()));
    mana_text.setPosition((view_size.x - mana_text.getGlobalBounds().width) / 2 - 80.f, view_size.y - 37.f);

    str_text.setString("SILA: " + std::to_string(player.get_strength()));
    str_text.setPosition((view_size.x - str_text.getGlobalBounds().width) / 2 + 70.f, view_size.y - 43.f);

    end_text.setString("WYTRZYMALOSC: " + std::to_string(player.get_endurance()));
    end_text.setPosition((view_size.x - end_text.getGlobalBounds().width) / 2 + 70.f, view_size.y - 30.f);

    int_text.setString("INTELIGENCJA: " + std::to_string(player.get_intelligence()));
    int_text.setPosition((view_size.x - int_text.getGlobalBounds().width) / 2 + 70.f, view_size.y - 17.f);

    points_text.setString(std::to_string(player.get_points()));
    points_text.setPosition((view_size.x - points_text.getGlobalBounds().width) / 2, 1.f);

    clock_text.setString("Czas gry: " + std::to_string(static_cast<int>(game_time)));
    clock_text.setPosition((view_size.x - clock_text.getLocalBounds().width), 1.f);

    for (int i = 0; i < 22; i++)
        window.draw(interface_backgrounds[i]);
    window.draw(portrait);
    window.draw(name_text);
    window.draw(class_text);
    window.draw(lvl_text);
    window.draw(exp_text);
    window.draw(hp_text);
    window.draw(mana_text);
    for (int i = 0; i < 4; i++)
        window.draw(spells[i]);
    for (int i = 0; i < 2; i++)
        window.draw(weapons[i]);
    window.draw(str_text);
    window.draw(end_text);
    window.draw(int_text);
    for (int i = 0; i < 3; i++)
        window.draw(options[i]);
    window.draw(points_text);
    window.draw(clock_text);
}

void Game::set_interface()
{
    int j = 0;
    for (int i = 0; i < 22; i++)
    {
        interface_backgrounds.push_back(sf::Sprite());
        interface_backgrounds[i].setTexture(Resources::get_resources().get_texture("images/Interface/Background.png"));
        interface_backgrounds[i].setScale(0.75f, 0.75f);
        interface_backgrounds[i].setOrigin(interface_backgrounds[i].getGlobalBounds().width, 0.f);
        if (i < 11)
            interface_backgrounds[i].setPosition(52.5f * i, view_size.y - 52.5f);
        else
        {
            interface_backgrounds[i].setPosition(52.5f * j, -40.f);
            j++;
        }
    }

    portrait.setScale(0.36f, 0.36f);
    portrait.setPosition(9.f, view_size.y - 44.f);

    for (int i = 0; i < 2; i++)
        weapons.push_back(sf::Sprite());
    weapons[0].setScale(0.33f, 0.33f);
    weapons[1].setScale(0.33f, 0.33f);
    weapons[0].setPosition((view_size.x - weapons[0].getGlobalBounds().width) / 2 - 10.f, view_size.y - 47.f);
    weapons[1].setPosition((view_size.x - weapons[1].getGlobalBounds().width) / 2 - 10.f, view_size.y - 23.f);

    for (int i = 0; i < 3; i++)
    {
        options.push_back(sf::Sprite());
        options[i].setScale(0.33f, 0.33f);
        options[i].setPosition(view_size.x - options[0].getGlobalBounds().width - 120.f + 40.f * i, view_size.y - 42.f);
    }
    options[0].setTexture(Resources::get_resources().get_texture("images/Interface/Spells.png"));
    options[1].setTexture(Resources::get_resources().get_texture("images/Interface/Equipment.png"));
    options[2].setTexture(Resources::get_resources().get_texture("images/Interface/Settings.png"));

    for (int i = 0; i < 4; i++)
    {
        spells.push_back(sf::Sprite());
        spells[i].setScale(0.33f, 0.33f);
        spells[i].setPosition((view_size.x - hp_text.getGlobalBounds().width) / 2 - 132.f + 29 * i, view_size.y - 23.f);
    }

    character_class char_class = player.get_class();

    if (char_class == character_class::fighter)
    {
        class_text.setString("WOJOWNIK");
        portrait.setTexture(Resources::get_resources().get_texture("images/Portraits/Fighter.png"));
        weapons[0].setTexture(Resources::get_resources().get_texture("images/Weapons/Sword.png"));
        weapons[1].setTexture(Resources::get_resources().get_texture("images/Weapons/Shield.png"));
        spells[0].setTexture(Resources::get_resources().get_texture("images/Spells/Stun.png"));
        spells[1].setTexture(Resources::get_resources().get_texture("images/Spells/Healing.png"));
        spells[2].setTexture(Resources::get_resources().get_texture("images/Spells/None.png"));
        spells[3].setTexture(Resources::get_resources().get_texture("images/Spells/None.png"));
    }
    if (char_class == character_class::ranger)
    {
        class_text.setString("STRZELEC");
        portrait.setTexture(Resources::get_resources().get_texture("images/Portraits/Ranger.png"));
        weapons[0].setTexture(Resources::get_resources().get_texture("images/Weapons/Bow.png"));
        weapons[1].setTexture(Resources::get_resources().get_texture("images/Weapons/Knife.png"));
        spells[0].setTexture(Resources::get_resources().get_texture("images/Spells/Aimedshot.png"));
        spells[1].setTexture(Resources::get_resources().get_texture("images/Spells/Healing.png"));
        spells[2].setTexture(Resources::get_resources().get_texture("images/Spells/None.png"));
        spells[3].setTexture(Resources::get_resources().get_texture("images/Spells/None.png"));
    }
    if (char_class == character_class::wizard)
    {
        class_text.setString("CZARODZIEJ");
        portrait.setTexture(Resources::get_resources().get_texture("images/Portraits/Wizard.png"));
        weapons[0].setTexture(Resources::get_resources().get_texture("images/Weapons/Staff.png"));
        weapons[1].setTexture(Resources::get_resources().get_texture("images/Weapons/Book.png"));
        spells[0].setTexture(Resources::get_resources().get_texture("images/Spells/Fireball.png"));
        spells[1].setTexture(Resources::get_resources().get_texture("images/Spells/Lightning.png"));
        spells[2].setTexture(Resources::get_resources().get_texture("images/Spells/Flurry.png"));
        spells[3].setTexture(Resources::get_resources().get_texture("images/Spells/Healing.png"));
    }

    name_text = char_select.get_name_text();
    name_text.setCharacterSize(8);
    name_text.setFillColor(sf::Color::White);

    class_text.setFont(game_font);
    class_text.setCharacterSize(8);

    lvl_text.setFont(game_font);
    lvl_text.setCharacterSize(8);

    exp_text.setFont(game_font);
    exp_text.setCharacterSize(8);

    hp_text.setFont(game_font);
    hp_text.setCharacterSize(8);
    hp_text.setFillColor(sf::Color(255, 26, 26));

    mana_text.setFont(game_font);
    mana_text.setCharacterSize(8);
    mana_text.setFillColor(sf::Color(3, 177, 252));

    str_text.setFont(game_font);
    str_text.setCharacterSize(8);

    end_text.setFont(game_font);
    end_text.setCharacterSize(8);

    int_text.setFont(game_font);
    int_text.setCharacterSize(8);

    clock_text.setFont(game_font);
    clock_text.setCharacterSize(8);
    clock_text.setOrigin(10.f, 0.f);

    points_text.setFont(game_font);
    points_text.setCharacterSize(8);
}

bool Game::pause_game(sf::RenderWindow& window)
{
    pause_options current = pause_options::continue_game;
    sf::Text pause_text("PAUZA", game_font, 60);
    sf::Text continue_text("KONTYNUUJ", game_font, 50);
    sf::Text end_text("ZAKONCZ", game_font, 50);
    sf::Text controls_text("STEROWANIE", game_font, 60);
    std::vector<sf::Text> controls(4, sf::Text("", game_font, 40));
    controls[0].setString("WSAD / STRZALKI   -   PORUSZANIE SIE");
    controls[1].setString("LPM   -   PIERWSZY ATAK");
    controls[2].setString("PPM   -   DRUGI ATAK");
    controls[3].setString("NUM 1-4   -   ZAKLECIA");
    pause_text.setPosition((window.getSize().x - pause_text.getLocalBounds().width) / 2, 50.f);
    continue_text.setPosition((window.getSize().x - continue_text.getGlobalBounds().width) / 2, 225.f);
    end_text.setPosition((window.getSize().x - end_text.getGlobalBounds().width) / 2, 325.f);
    controls_text.setPosition((window.getSize().x - controls_text.getGlobalBounds().width) / 2, 500.f);
    for (int i = 0; i < 4; i++)
    {
        controls[i].setPosition((window.getSize().x - controls[i].getGlobalBounds().width) / 2, 100.f * (i+1) + 550.f);
    }
    pause_text.setFillColor(sf::Color::Red);
    continue_text.setFillColor(sf::Color::Yellow);
    controls_text.setFillColor(sf::Color::Red);

    sf::Event event;
    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Enter)
                {
                    if (current == pause_options::continue_game)
                    {
                        clock.restart().asSeconds();
                        return true;
                    }
                    else return false;
                }
                if (event.key.code == sf::Keyboard::Escape)
                {
                    clock.restart().asSeconds();
                    return true;
                }
                if (event.key.code == sf::Keyboard::Up)
                {
                    current = pause_options::continue_game;
                    continue_text.setFillColor(sf::Color::Yellow);
                    end_text.setFillColor(sf::Color::White);
                }
                else if (event.key.code == sf::Keyboard::Down)
                {
                    current = pause_options::end;
                    end_text.setFillColor(sf::Color::Yellow);
                    continue_text.setFillColor(sf::Color::White);
                }
            }
        }
        window.clear();
        window.setView(window.getDefaultView());
        window.draw(background);
        window.draw(pause_text);
        window.draw(continue_text);
        window.draw(end_text);
        window.draw(controls_text);
        for (int i = 0; i < 4; i++)
        {
            window.draw(controls[i]);
        }
        window.display();
    }
    return true;
}

void Game::spellbook(sf::RenderWindow& window)
{
    sf::Text spellbook_text("KSIEGA ZAKLEC", game_font, 60);
    std::vector<sf::Text> names(4, sf::Text("", game_font, 40));
    std::vector<sf::Text> effects(4, sf::Text("", game_font, 30));
    std::vector<sf::Text> descriptions(4, sf::Text("", game_font, 30));

    if (player.get_class() == character_class::fighter)
    {
        names[0].setString("OGLUSZENIE");
        effects[0].setString("Obrazenia: sila, oglusza przeciwnika na 3 sekundy.");
        descriptions[0].setString("Koszt: 1 many");
        names[1].setString("LECZENIE");
        effects[1].setString("Przywraca 1 punkt zycia.");
        descriptions[1].setString("Koszt: 2 many");
    }
    if (player.get_class() == character_class::ranger)
    {
        names[0].setString("WYMIERZONY STRZAL");
        effects[0].setString("Obrazenia: 2 * sila");
        descriptions[0].setString("Koszt: 1 many");
        names[1].setString("LECZENIE");
        effects[1].setString("Przywraca 1 punkt zycia.");
        descriptions[1].setString("Koszt: 2 many");
    }
    if (player.get_class() == character_class::wizard)
    {
        names[0].setString("OGNISTY POCISK");
        effects[0].setString("Obrazenia: inteligencja");
        descriptions[0].setString("Koszt: 1 many");
        names[1].setString("BLYSKAWICA");
        effects[1].setString("Obrazenia: 2 * inteligencja");
        descriptions[1].setString("Koszt: 2 many");
        names[2].setString("LODOWY POCISK");
        effects[2].setString("Obrazenia: inteligencja, spowalnia przeciwnika na 5 sekund");
        descriptions[2].setString("Koszt: 2 many");
        names[3].setString("LECZENIE");
        effects[3].setString("Przywraca 1 punkt zycia.");
        descriptions[3].setString("Koszt: 2 many");
    }

    spellbook_text.setPosition((window.getSize().x - spellbook_text.getLocalBounds().width) / 2, 50.f);
    spellbook_text.setFillColor(sf::Color::Red);

    for (int i = 0; i < 4; i++)
    {
        spells[i].setScale(3.f, 3.f);
        spells[i].setPosition(50.f, 225.f * (i + 1) - 50.f);
        names[i].setPosition(60.f + spells[i].getGlobalBounds().width, spells[i].getGlobalBounds().top);
        names[i].setFillColor(sf::Color::Yellow);
        effects[i].setPosition(60.f + spells[i].getGlobalBounds().width, names[i].getPosition().y + 70.f);
        descriptions[i].setPosition(60.f + spells[i].getGlobalBounds().width, effects[i].getPosition().y + 60.f);
    }

    sf::Event event;
    while (window.isOpen())
    {
        window.clear();
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Enter || event.key.code == sf::Keyboard::Escape)
                {
                    for (int i = 0; i < 4; i++)
                    {
                        spells[i].setScale(0.33f, 0.33f);
                        spells[i].setPosition((view_size.x - hp_text.getGlobalBounds().width) / 2 - 103.f + 29 * i, view_size.y - 23.f);
                    }
                    clock.restart().asSeconds();
                    return;
                }
            }
        }
        window.setView(window.getDefaultView());
        window.draw(background);
        window.draw(spellbook_text);
        for (int i = 0; i < 4; i++)
        {
            window.draw(spells[i]);
            window.draw(names[i]);
            window.draw(effects[i]);
            window.draw(descriptions[i]);
        }
        window.display();
    }
    return;
}

void Game::equipment(sf::RenderWindow& window)
{
    sf::Text equipment_text("EKWIPUNEK", game_font, 60);
    std::vector<sf::Text> names(2, sf::Text("", game_font, 40));
    std::vector<sf::Text> effects(2, sf::Text("", game_font, 30));
    std::vector<sf::Text> descriptions(2, sf::Text("", game_font, 30));
    descriptions[0].setStyle(sf::Text::Style::Italic);
    descriptions[1].setStyle(sf::Text::Style::Italic);

    if (player.get_class() == character_class::fighter)
    {
        names[0].setString("MIECZ");
        effects[0].setString("Obrazenia: sila");
        descriptions[0].setString("Zwykly zelazny miecz.");
        names[1].setString("TARCZA");
        effects[1].setString("Zapewnia ochrone przed ciosami przeciwnikow na 0,75 sekundy.");
        descriptions[1].setString("Zwykla drewniana tarcza.");
    }
    if (player.get_class() == character_class::ranger)
    {
        names[0].setString("LUK");
        effects[0].setString("Obrazenia: sila");
        descriptions[0].setString("Zwykly drewniany luk.");
        names[1].setString("SZTYLET");
        effects[1].setString("Obrazenia: sila + 2");
        descriptions[1].setString("Zwykly zelazny sztylet.");
    }
    if (player.get_class() == character_class::wizard)
    {
        names[0].setString("KOSTUR");
        effects[0].setString("Obrazenia: sila");
        descriptions[0].setString("Drewniany kostur czarodzieja.");
        names[1].setString("KSIEGA ZAKLEC");
        effects[1].setString("Regeneruje mane uzywajacego ja czarodzieja.");
        descriptions[1].setString("Ladnie oprawiona ksiega zaklec.");
    }

    equipment_text.setPosition((window.getSize().x - equipment_text.getLocalBounds().width) / 2, 50.f);
    equipment_text.setFillColor(sf::Color::Red);

    weapons[0].setScale(3.f, 3.f);
    weapons[0].setPosition(50.f, 300.f);
    weapons[1].setScale(3.f, 3.f);
    weapons[1].setPosition(50.f, 600.f);
    names[0].setPosition(60.f + weapons[0].getGlobalBounds().width, weapons[0].getGlobalBounds().top);
    names[1].setPosition(60.f + weapons[1].getGlobalBounds().width, weapons[1].getGlobalBounds().top);
    names[0].setFillColor(sf::Color::Yellow);
    names[1].setFillColor(sf::Color::Yellow);
    effects[0].setPosition(60.f + weapons[0].getGlobalBounds().width, names[0].getPosition().y + 70.f);
    effects[1].setPosition(60.f + weapons[1].getGlobalBounds().width, names[1].getPosition().y + 70.f);
    descriptions[0].setPosition(60.f + weapons[0].getGlobalBounds().width, effects[0].getPosition().y + 70.f);
    descriptions[1].setPosition(60.f + weapons[1].getGlobalBounds().width, effects[1].getPosition().y + 70.f);

    sf::Event event;
    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Enter || event.key.code == sf::Keyboard::Escape)
                {
                    weapons[0].setScale(0.33f, 0.33f);
                    weapons[1].setScale(0.33f, 0.33f);
                    weapons[0].setPosition((view_size.x - weapons[0].getGlobalBounds().width) / 2, view_size.y - 47.f);
                    weapons[1].setPosition((view_size.x - weapons[1].getGlobalBounds().width) / 2, view_size.y - 23.f);
                    clock.restart().asSeconds();
                    return;
                }
            }
        }
        window.clear();
        window.setView(window.getDefaultView());
        window.draw(background);
        window.draw(equipment_text);
        window.draw(weapons[0]);
        window.draw(weapons[1]);
        window.draw(names[0]);
        window.draw(names[1]);
        window.draw(effects[0]);
        window.draw(effects[1]);
        window.draw(descriptions[0]);
        window.draw(descriptions[1]);
        window.display();
    }
    return;
}