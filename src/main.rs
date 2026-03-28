mod readline;
use readline::terminal::RawMode;
use std::io::Read;

fn main()
{
    let _raw = RawMode::enable();

    println!("RawMod is enable. Press ESC for escape !\r");

    let mut buffer = [0u8; 1];

    loop
    {
        std::io::stdin().read_exact(&mut buffer).unwrap();
        print!("byte : {}\r\n", buffer[0]);
        
        if buffer[0] == 27 { break ;}
    }
}
