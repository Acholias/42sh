mod readline;
use readline::terminal::RawMode;
use readline::input::{read_action, Action};
use readline::display::Display;

fn main()
{
    let _raw = RawMode::enable();
    let _display = Display::new("42sh> ");

    let buffer: Vec<char> = vec!['h', 'e', 'l', 'l', 'o'];
    let cursor = 5;

    _display.render(&buffer, cursor);

    read_action();
    _display.newline();
}
