use libc::{tcgetattr, tcsetattr, termios, STDIN_FILENO, TCSANOW};
use std::mem;

pub struct RawMode {
    original:   termios,
}

impl    RawMode {
    pub fn enable() -> Self
    {
        let mut termios = unsafe { mem::zeroed::<termios>() };

        unsafe { tcgetattr(STDIN_FILENO, &mut termios) };

        let original = termios;

        termios.c_lflag &= !(libc::ICANON | libc::ECHO);

        termios.c_cc[libc::VMIN] = 1;
        termios.c_cc[libc::VTIME] = 0;

        unsafe { tcsetattr(STDIN_FILENO, TCSANOW, &termios) };

        RawMode { original }
    }
}

impl Drop for RawMode {
    fn drop(&mut self)
    {
        unsafe { tcsetattr(STDIN_FILENO, TCSANOW, &self.original) };
    }
}
