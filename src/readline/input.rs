use std::io::Read;

pub enum Action {
    MoveLeft,
    MoveRight,
    MoveUp,
    MoveDown,
    Home,               // CTRL + A -> Aller au début de la ligne
    End,                // CTRL + E -> Aller à la fin de la ligne
    Clear,              // CTRL + U -> Effacer toute la ligne avant le curseur
    ClearAfter,         // CTRL + K -> Effacer toute la ligne après le curseur
    Backspace,
    Enter,
    Char(char),
    CtrlD,
    CtrlC,
    CtrlL,
    CtrlW,
    Unknown,
}

pub fn read_action() -> Action
{
    let mut buffer = [0u8; 1];

    std::io::stdin().read_exact(&mut buffer).unwrap();

    match buffer[0]
    {
        27 =>
        {
            std::io::stdin().read_exact(&mut buffer).unwrap();
            if buffer[0] == 91
            {
                std::io::stdin().read_exact(&mut buffer).unwrap();
                match buffer[0]
                {
                    65 => Action::MoveUp,
                    66 => Action::MoveDown,
                    67 => Action::MoveRight,
                    68 => Action::MoveLeft,
                    _  => Action::Unknown,
                }
            }
            else { Action::Unknown }
        }

        1           => Action::Home,
        3           => Action::CtrlC,
        4           => Action::CtrlD,
        12          => Action::CtrlL,
        23          => Action::CtrlW,
        5           => Action::End,
        11          => Action::ClearAfter,
        21          => Action::Clear,
        10          => Action::Enter,
        127         => Action::Backspace,
        32..=126    => Action::Char(buffer[0] as char),
        _           => Action::Unknown,
    }
}
