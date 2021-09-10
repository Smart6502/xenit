#[macro_export]
macro_rules! log
{
    ($loglevel:literal, $fmt:expr $(, $p:expr )*) =>
    {
        let llvs = match $loglevel
        {
            0 => "94minfo",
            1 => "93mwarn",
            2 => "91mfail",
            _ => "none",
        };

        println!("\x1b[1;{}\x1b[0m: {}", llvs, format!($fmt, $($p),*));
    }
}

#[macro_export]
macro_rules! info
{
    ($fmt: expr $(, $p:expr )*) =>
    {
        log!(0, $fmt $(,$p)*);
    }
}

#[macro_export]
macro_rules! warn
{
    ($fmt: expr $(, $p:expr )*) =>
    {
        log!(1, $fmt $(,$p)*);
    }
}

#[macro_export]
macro_rules! fail
{
    ($fmt: expr $(, $p:expr )*) =>
    {
        log!(2, $fmt $(,$p)*);
    }
}
