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
    CtrlD,              // Exit shell
    CtrlC,
    CtrlL,              // clear terminal
    CtrlW,              // Efface le premier mot avant le curseur
    CtrlY,              // Colle le kill_ring
    CtrlT,              // Inverser deux caractere
    CtrlAL,             // ctrl + fleche de gauche
    CtrlAR,             // ctrl + fleche de droite
	CtrlR,				// Ouvre le mode de recherche pour l'historique
	CtrlG,				// Quitte le mode recherche avec l'historique
    AltF,               // Avance le curseur de un mot
    AltB,               // Recule le curseur de un mot
    AltD,               // Efface le premier mot apres le curseur
    AltU,               // met le mot en majuscule
    AltL,               // met le mot en minuscule
    AltC,               // Capitalize la premiere lettre du mot
    AltT,               // Inverse les mots (comme le CTRL + T mais sur 2 mots)
    AltDot,             // Insere sur le buffer le dernier arguments de l'historique
    AltHash,            // Commente la ligne
    Unknown,
}

pub fn read_action() -> Action
{
    let mut buffer = [0u8; 1];

    std::io::stdin().read_exact(&mut buffer).unwrap();
    match buffer[0]
    {
        27          => read_escape_sequence(),
        1           => Action::Home,
        3           => Action::CtrlC,
        4           => Action::CtrlD,
        5           => Action::End,
		7			=> Action::CtrlG,
        10          => Action::Enter,
        11          => Action::ClearAfter,
        12          => Action::CtrlL,
		18			=> Action::CtrlR,
        20          => Action::CtrlT,
        21          => Action::Clear,
        23          => Action::CtrlW,
        25          => Action::CtrlY,
        127         => Action::Backspace,
        32..=126    => Action::Char(buffer[0] as char),
        _           => Action::Unknown,
    }
}

fn  read_escape_sequence() -> Action
{
    let mut buffer = [0u8; 1];

    std::io::stdin().read_exact(&mut buffer).unwrap();
    if buffer[0] == 91
    {
        read_csi_sequence()
    }
    else
    {
        read_alt_sequence(buffer[0])
    }
}

fn  read_csi_sequence() -> Action
{
    let mut buffer = [0u8; 1];
    std::io::stdin().read_exact(&mut buffer).unwrap();

    match buffer[0]
    {
        65  => Action::MoveUp,
        66  => Action::MoveDown,
        67  => Action::MoveRight,
        68  => Action::MoveLeft,
        49  => read_ctrl_arrow(),
        _   => Action::Unknown,
    }
}

fn  read_ctrl_arrow() -> Action
{
    let mut buffer = [0u8; 1];

    std::io::stdin().read_exact(&mut buffer).unwrap();
    std::io::stdin().read_exact(&mut buffer).unwrap();
    std::io::stdin().read_exact(&mut buffer).unwrap();
    match buffer[0]
    {
        67  => Action::CtrlAR,
        68  => Action::CtrlAL,
        _   => Action::Unknown,
    }
}

fn read_alt_sequence(byte: u8) -> Action
{
    match byte
    {
        102 => Action::AltF,
        98  => Action::AltB,
        100 => Action::AltD,
        99  => Action::AltC,
        108 => Action::AltL,
        116 => Action::AltT,
        117 => Action::AltU,
        35  => Action::AltHash,
        46  => Action::AltDot,
        _   => Action::Unknown,
    }
}
