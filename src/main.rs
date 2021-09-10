extern crate libc;

use libc::*;
use std::{ffi::CString, process::{exit, id}};

#[macro_use]
mod logger;
mod util;

fn main()
{
    if id() != 1
    {
        fail!("xenit has not been run as PID 1");
        exit(1);
    }

    util::open_stds();

    unsafe
    {
        let root = CString::new("/").unwrap();

        chdir(root.as_ptr());

        util::mount_needed("/proc", "/proc", "proc", MS_SYNCHRONOUS | MS_NOSUID | MS_NOEXEC);
        util::mount_needed("none" , "/tmp", "tmpfs", MS_SYNCHRONOUS);
        util::mount_needed("tmpfs", "/dev/shm", "tmpfs", MS_SYNCHRONOUS);
    }
}
