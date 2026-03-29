use std::fs::{File, OpenOptions};
use std::io::{BufRead, BufReader, Write};
use std::path::PathBuf;

pub struct History {
    entries:    Vec<String>,
    index:      usize,
    current:    String,
}

impl    History
{
    pub fn new() -> Self
    {
        let mut history  = History {
            entries:    Vec::new(),
            index:      0,
            current:    String::new(),
        };

        history.load();
        history.index = history.entries.len();

        history
    }

    fn path() -> PathBuf
    {
        let home = std::env::var("HOME").unwrap_or_else(|_| String::from("/tmp"));
        PathBuf::from(home).join(".42sh_history");
    }
}
