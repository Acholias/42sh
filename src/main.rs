mod readline;
use readline::terminal::RawMode;
use readline::editor::Editor;

fn main()
{
    let _raw = RawMode::enable();
    let mut editor = Editor::new("42sh> ");

    loop
    {
        let line = editor.read_line();
        println!("Command receive : {}", line);
    }
}
