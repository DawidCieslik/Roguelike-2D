#include "Menu.h"

void Menu::set_options(sf::Text options[], sf::Text& title)
{
    options[0].setString("ROZPOCZNIJ GRE");
    options[1].setString("NAJLEPSZE WYNIKI");
    options[2].setString("ZAKONCZ GRE");
    title.setPosition((window.getSize().x - title.getGlobalBounds().width) / 2, 200.f);
    title.setFillColor(sf::Color::Red);
    for (int i = 0; i < 3; i++)
    {
        options[i].setCharacterSize(50);
        options[i].setFont(game_font);
        options[i].setPosition((window.getSize().x - options[i].getGlobalBounds().width) / 2, 150.f * (i + 1) + 300.f);
    }
    options[0].setFillColor(sf::Color::Yellow);
}

void Menu::main_menu()
{
    load_levels();
    sf::Text title("ROGUELIKE 2D", game_font, 80);
    sf::Text options_text[3];
    set_options(options_text, title);
    menu_leaderboard.load_leaderboards();
    music.play();
    music.setLoop(true);
    std::vector<menu_options>::const_iterator iter = options.begin();
    sf::Event event;
    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Up && iter != options.begin())
                {
                    options_text[iter - options.begin()].setFillColor(sf::Color::White);
                    iter--;
                    options_text[iter - options.begin()].setFillColor(sf::Color::Yellow);
                }
                else if (event.key.code == sf::Keyboard::Down && next(iter, 1) != options.end())
                {
                    options_text[iter - options.begin()].setFillColor(sf::Color::White);
                    iter++;
                    options_text[iter - options.begin()].setFillColor(sf::Color::Yellow);
                }
                else if (event.key.code == sf::Keyboard::Enter)
                {
                    if ((*iter) == menu_options::play)
                    {
                        if (!start_game())
                            return;
                    }
                    else if ((*iter) == menu_options::leaderboards)
                        display_leaderboards();
                    else if ((*iter) == menu_options::end)
                    {
                        menu_leaderboard.save_leaderboards();
                        return;
                    }
                }
            }
        }
        window.clear();
        window.setView(window.getDefaultView());
        window.draw(background);
        window.draw(title);
        for (int i = 0; i < 3; i++)
            window.draw(options_text[i]);
        window.display();
    }
}

void Menu::display_leaderboards()
{
    sf::Text leaderboard("TABLICA WYNIKOW", game_font, 60);
    sf::Text continue_text("KONTYNUUJ", game_font, 40);
    sf::Text player("", game_font, 35);
    std::vector<sf::Text> results;
    leaderboard.setPosition((window.getSize().x - leaderboard.getGlobalBounds().width) / 2, 50.f);
    leaderboard.setFillColor(sf::Color::Red);
    continue_text.setPosition((window.getSize().x - continue_text.getGlobalBounds().width) / 2, 950.f);
    continue_text.setFillColor(sf::Color::Yellow);
    for (int i = 0; i < menu_leaderboard.get_entries().size(); i++)
    {
        player.setString(std::get<1>(menu_leaderboard.get_entries()[i]) + " (" + std::get<2>(menu_leaderboard.get_entries()[i]) + ") " + std::to_string(std::get<0>(menu_leaderboard.get_entries()[i])));
        player.setPosition((window.getSize().x - player.getGlobalBounds().width) / 2, 80.f * i + 150.f);
        results.push_back(player);
    }
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Enter)
                    return;
            }
        }
        window.clear();
        window.setView(window.getDefaultView());
        window.draw(background);
        window.draw(leaderboard);
        for (int i = 0; i < results.size(); i++)
            window.draw(results[i]);
        window.draw(continue_text);
        window.display();
    }
}

bool Menu::start_game()
{
    Game game;
    game.character_selection_menu(window);
    std::vector<std::string>::iterator iter;
    state_of_game state;
    for (iter = level_filenames.begin(); iter != level_filenames.end(); ++iter)
    {
        state = game.play_level(window, (*iter));
        if (state == state_of_game::lost)
        {
            end_screen();
            return true;
        }
        if (state == state_of_game::file_error || state == state_of_game::error)
            return false;
    }
    game.subtract_points_for_time();
    if (std::get<0>(menu_leaderboard.get_entries().back()) < game.get_player_points() || menu_leaderboard.get_entries().size() < 10)
        end_screen_with_leaderboards(game.get_player_points(), game.get_player_name(), game.get_player_class());
    else end_screen();
    return true;
}

void Menu::end_screen()
{
    sf::Text end_text("KONIEC GRY", game_font, 60);
    sf::Text continue_text("KONTYNUUJ", game_font, 50);
    end_text.setPosition((window.getSize().x - end_text.getGlobalBounds().width) / 2, 350.f);
    end_text.setFillColor(sf::Color::Red);
    continue_text.setPosition((window.getSize().x - continue_text.getGlobalBounds().width) / 2, 525.f);
    continue_text.setFillColor(sf::Color::Yellow);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::KeyPressed)
                if (event.key.code == sf::Keyboard::Enter)
                    return;
        }
        window.clear();
        window.setView(window.getDefaultView());
        window.draw(background);
        window.draw(end_text);
        window.draw(continue_text);
        window.display();
    }
}

void Menu::end_screen_with_leaderboards(int player_points, sf::Text player_name, sf::Text player_class)
{
    sf::Text end_text("KONIEC GRY", game_font, 60);
    sf::Text continue_text("KONTYNUUJ", game_font, 50);
    sf::Text points(std::to_string(player_points), game_font, 40);
    end_text.setPosition((window.getSize().x - end_text.getGlobalBounds().width) / 2, 350.f);
    end_text.setFillColor(sf::Color::Red);
    continue_text.setPosition((window.getSize().x - continue_text.getGlobalBounds().width) / 2, 525.f);
    continue_text.setFillColor(sf::Color::Yellow);
    player_name.setCharacterSize(40);
    player_name.setPosition((window.getSize().x - player_name.getGlobalBounds().width) / 2, 650.f);
    player_class.setCharacterSize(40);
    player_class.setPosition((window.getSize().x - player_class.getGlobalBounds().width) / 2, 750.f);
    points.setPosition((window.getSize().x - points.getGlobalBounds().width) / 2, 850.f);

    sf::Event event;
    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Enter)
                {
                    menu_leaderboard.add_to_leaderboard(player_points, player_name.getString(), player_class.getString());
                    return;
                }
            }
        }
        window.clear();
        window.setView(window.getDefaultView());
        window.draw(background);
        window.draw(end_text);
        window.draw(continue_text);
        window.draw(player_name);
        window.draw(player_class);
        window.draw(points);
        window.display();
    }
}

void Menu::load_levels()
{
    std::string nazwa_pliku;
    for (const auto& entry : std::filesystem::directory_iterator(path))
    {
        nazwa_pliku = entry.path().u8string();
        level_filenames.push_back(nazwa_pliku);
    }
}