use libc::*;
use std::ffi::CString;

pub fn open_stds()
{
    let confile = CString::new("/dev/console").unwrap();
    let confref = confile.as_ptr();

    unsafe
    {
        let ofd = open(confref, O_RDONLY, 0);
        dup2(ofd, STDIN_FILENO);

        let tfd = open(confref, O_RDWR, 0);
        dup2(tfd, STDOUT_FILENO);
        dup2(tfd, STDERR_FILENO);

        if ofd > 2
        {
            close(ofd);    
        }

        if tfd > 2
        {
            close(tfd);
        }
    }
}

pub fn rmount(spfile: &str, dir: &str, fstype: &str, rwflag: c_ulong)
{
    let spfc = CString::new(spfile).unwrap();
    let dirc = CString::new(dir).unwrap();
    let fstypec = CString::new(fstype).unwrap();
    let edata = CString::new("").unwrap();

    unsafe
    {
        if mount(spfc.as_ptr(), dirc.as_ptr(), fstypec.as_ptr(), rwflag, edata.as_ptr() as *const c_void) != 0
        {
            fail!("mounting {} failed", spfile);
        }
        else
        {
            info!("mounted {}", spfile);
        }
    }
}

pub fn mount_needed(spfile: &str, dir: &str, fstype: &str, rwflag: c_ulong)
{
    let dirc = CString::new(dir).unwrap();

    unsafe
    {
        if mkdir(dirc.as_ptr(), S_IFDIR) != 0
        {
            fail!("could not create directory {} for mounting {}", dir, spfile);
        }
        else
        {
            rmount(spfile, dir, fstype, rwflag);    
        }    
    }
}
