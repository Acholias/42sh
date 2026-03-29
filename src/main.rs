mod readline;
use readline::terminal::RawMode;
use readline::input::read_action;
use readline::input::Action;

fn main() {
    let _raw = RawMode::enable();

    println!("Appuie sur des touches (Ctrl+C pour quitter)\r");

    loop
    {
        match read_action()
        {
            Action::MoveLeft    => print!("← \r\n"),
            Action::MoveRight   => print!("→ \r\n"),
            Action::MoveUp      => print!("↑ \r\n"),
            Action::MoveDown    => print!("↓ \r\n"),
            Action::Home        => print!("Home (Ctrl+A)\r\n"),
            Action::End         => print!("End (Ctrl+E)\r\n"),
            Action::Clear       => print!("Clear (Ctrl+U)\r\n"),
            Action::ClearAfter  => print!("ClearAfter (Ctrl+K)\r\n"),
            Action::Backspace   => print!("Backspace\r\n"),
            Action::Enter       => print!("Enter\r\n"),
            Action::Char(c)     => print!("Char: {}\r\n", c),
            Action::Unknown     => {}
        }
    }
}
