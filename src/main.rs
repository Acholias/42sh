mod readline;
use readline::terminal::RawMode;
use readline::editor::Editor;

fn main()
{
    let _raw = RawMode::enable();
    let mut editor = Editor::new("42sh> ");

    loop
    {
        match editor.readline()
        {
            Some(line)  =>  println!("Line catch with read_line : {}", line),
            None        => break,
        }
    }
}
