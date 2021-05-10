#include "Character_selection.h"

void Character_selection::select_class_menu(sf::RenderWindow& window)
{
    std::string name = "";

    sf::Text player_text("NAZWA GRACZA", game_font, 60);
    player_text.setFillColor(sf::Color::Yellow);
    player_text.setPosition((1920.f - player_text.getGlobalBounds().width) / 2, 30.f);

    sf::Text continue_text("WPISZ NAZWE GRACZA, WYBIERZ KLASE POSTACI ZA POMOCA STRZALEK, A NASTEPNIE KLIKNIJ ENTER, BY KONTYNUOWAC", game_font, 22);
    continue_text.setFillColor(sf::Color::Yellow);
    continue_text.setOrigin(continue_text.getLocalBounds().width / 2, continue_text.getLocalBounds().height);
    continue_text.setPosition(955.f, 1070.f);

    sf::RectangleShape field;
    field.setSize(sf::Vector2f(500, 50));
    field.setFillColor(sf::Color::White);
    field.setOutlineColor(sf::Color(127, 127, 127));
    field.setOutlineThickness(2);
    field.setPosition((1920.f - field.getGlobalBounds().width) / 2, (1080.f - field.getGlobalBounds().height) / 2 - 375.f);

    std::vector<sf::Sprite> portraits(3, sf::Sprite());
    portraits[0].setTexture(Resources::get_resources().get_texture("images/Portraits/Fighter.png"));
    portraits[1].setTexture(Resources::get_resources().get_texture("images/Portraits/Ranger.png"));
    portraits[2].setTexture(Resources::get_resources().get_texture("images/Portraits/Wizard.png"));
    portraits[0].setScale(2.f, 2.f);
    portraits[1].setScale(2.f, 2.f);
    portraits[2].setScale(2.f, 2.f);
    portraits[0].setPosition((1920 - portraits[0].getGlobalBounds().width) / 2 - 500.f, 250.f);
    portraits[1].setPosition((1920 - portraits[1].getGlobalBounds().width) / 2, 250.f);
    portraits[2].setPosition((1920 - portraits[2].getGlobalBounds().width) / 2 + 500.f, 250.f);

    std::vector<sf::Text> descriptions(21, sf::Text());
    descriptions[0].setString("WOJOWNIK");
    descriptions[1].setString("STRZELEC");
    descriptions[2].setString("CZARODZIEJ");
    descriptions[3].setString("ZYCIE: 12");
    descriptions[4].setString("ZYCIE: 8");
    descriptions[5].setString("ZYCIE: 8");
    descriptions[6].setString("MANA: 2");
    descriptions[7].setString("MANA: 2");
    descriptions[8].setString("MANA: 5");
    descriptions[9].setString("SILA: 5");
    descriptions[10].setString("SILA: 4");
    descriptions[11].setString("SILA: 3");
    descriptions[12].setString("WYTRZYMALOSC: 6");
    descriptions[13].setString("WYTRZYMALOSC: 4");
    descriptions[14].setString("WYTRZYMALOSC: 4");
    descriptions[15].setString("INTELIGENCJA: 2");
    descriptions[16].setString("INTELIGENCJA: 2");
    descriptions[17].setString("INTELIGENCJA: 5");

    descriptions[0].setFillColor(sf::Color::Yellow);
    int j = 0, k = 0, l = 0;
    for (int i = 0; i < 18; i++)
    {
        descriptions[i].setFont(game_font);
        descriptions[i].setCharacterSize(30);
        if (i < 3)
            descriptions[i].setStyle(sf::Text::Bold);
        if (i >= 3 && i < 6)
            descriptions[i].setFillColor(sf::Color(255, 26, 26));
        if (i >= 6 && i < 9)
            descriptions[i].setFillColor(sf::Color(3, 177, 252));

        if (i % 3 == 0)         //WOJOWNIK
        {
            descriptions[i].setPosition((1920.f - descriptions[i].getGlobalBounds().width) / 2 - 500.f, 460.f + 60 * j);
            j++;
        }
        else if (i % 3 == 1)    //STRZELEC
        {
            descriptions[i].setPosition((1920.f - descriptions[i].getGlobalBounds().width) / 2, 460.f + 60 * k);
            k++;
        }
        else if (i % 3 == 2)    //CZARODZIEJ
        {
            descriptions[i].setPosition((1920.f - descriptions[i].getGlobalBounds().width) / 2 + 500.f, 460.f + 60 * l);
            l++;
        }
    }

    std::vector<sf::Sprite> weapons(6, sf::Sprite());
    weapons[0].setTexture(Resources::get_resources().get_texture("images/Weapons/Sword.png"));
    weapons[1].setTexture(Resources::get_resources().get_texture("images/Weapons/Shield.png"));
    weapons[2].setTexture(Resources::get_resources().get_texture("images/Weapons/Bow.png"));
    weapons[3].setTexture(Resources::get_resources().get_texture("images/Weapons/Knife.png"));
    weapons[4].setTexture(Resources::get_resources().get_texture("images/Weapons/Staff.png"));
    weapons[5].setTexture(Resources::get_resources().get_texture("images/Weapons/Book.png"));
    weapons[0].setPosition((1920.f - weapons[0].getGlobalBounds().width) / 2 - 650.f, 1080.f - 240.f);
    weapons[1].setPosition((1920.f - weapons[1].getGlobalBounds().width) / 2 - 650.f, 1080.f - 170.f);
    weapons[2].setPosition((1920.f - weapons[2].getGlobalBounds().width) / 2 - 150.f, 1080.f - 240.f);
    weapons[3].setPosition((1920.f - weapons[3].getGlobalBounds().width) / 2 - 150.f, 1080.f - 170.f);
    weapons[4].setPosition((1920.f - weapons[4].getGlobalBounds().width) / 2 + 350.f, 1080.f - 240.f);
    weapons[5].setPosition((1920.f - weapons[5].getGlobalBounds().width) / 2 + 350.f, 1080.f - 170.f);

    std::vector<sf::Sprite> spells(12, sf::Sprite());
    spells[0].setTexture(Resources::get_resources().get_texture("images/Spells/Stun.png"));
    spells[1].setTexture(Resources::get_resources().get_texture("images/Spells/Healing.png"));
    spells[2].setTexture(Resources::get_resources().get_texture("images/Spells/None.png"));
    spells[3].setTexture(Resources::get_resources().get_texture("images/Spells/None.png"));
    spells[4].setTexture(Resources::get_resources().get_texture("images/Spells/Aimedshot.png"));
    spells[5].setTexture(Resources::get_resources().get_texture("images/Spells/Healing.png"));
    spells[6].setTexture(Resources::get_resources().get_texture("images/Spells/None.png"));
    spells[7].setTexture(Resources::get_resources().get_texture("images/Spells/None.png"));
    spells[8].setTexture(Resources::get_resources().get_texture("images/Spells/Fireball.png"));
    spells[9].setTexture(Resources::get_resources().get_texture("images/Spells/Lightning.png"));
    spells[10].setTexture(Resources::get_resources().get_texture("images/Spells/Flurry.png"));
    spells[11].setTexture(Resources::get_resources().get_texture("images/Spells/Healing.png"));
    for (int i = 0; i < 12; i++)
    {
        if (i < 4)
            spells[i].setPosition((1920.f - spells[i].getGlobalBounds().width) / 2 - 550.f + 70 * i, 1080.f - 205.f);
        if (i >= 4 && i < 8)
            spells[i].setPosition((1920.f - spells[i].getGlobalBounds().width) / 2 - 50.f - 280.f + 70 * i, 1080.f - 205.f);
        if (i >= 8)
            spells[i].setPosition((1920.f - spells[i].getGlobalBounds().width) / 2 + 450.f - 560.f + 70 * i, 1080.f - 205.f);
    }

    std::vector<character_class>::const_iterator iter = characters.begin();
    sf::Event event;

    while (window.isOpen())
    {
        window.clear();
        while (window.pollEvent(event))
        {
            name_text.setPosition(sf::Vector2f((1920.f - name_text.getGlobalBounds().width) / 2 - 10.f, field.getGlobalBounds().top + 2.f));
            if (event.type == sf::Event::TextEntered && (event.text.unicode == 8 || event.text.unicode == 32 || (event.text.unicode >= 65 && event.text.unicode <= 90) || (event.text.unicode >= 97 && event.text.unicode <= 122)))
            {
                if (event.text.unicode != 8 && event.text.unicode != 32 && name.length() < 10)
                    name += toupper(static_cast<char>(event.text.unicode));
                else if (event.text.unicode == 8 && name.length() > 0)
                    name = name.erase(name.size() - 1, name.size());
                name_text.setString(name);
            }
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Left && iter != characters.begin())
                {
                    descriptions[iter - characters.begin()].setFillColor(sf::Color::White);
                    iter--;
                    descriptions[iter - characters.begin()].setFillColor(sf::Color::Yellow);
                }
                if (event.key.code == sf::Keyboard::Right && next(iter, 1) != characters.end())
                {
                    descriptions[iter - characters.begin()].setFillColor(sf::Color::White);
                    iter++;
                    descriptions[iter - characters.begin()].setFillColor(sf::Color::Yellow);
                }
                if (event.key.code == sf::Keyboard::Enter)
                {
                    player_class = (*iter);
                    return;
                }
            }
        }

        window.draw(background);
        window.draw(player_text);
        window.draw(field);
        window.draw(name_text);
        for (int i = 0; i < 3; i++)
            window.draw(portraits[i]);
        for (int i = 0; i < 18; i++)
            window.draw(descriptions[i]);
        for (int i = 0; i < 6; i++)
            window.draw(weapons[i]);
        for (int i = 0; i < 12; i++)
            window.draw(spells[i]);
        window.draw(continue_text);
        window.display();
    }
}