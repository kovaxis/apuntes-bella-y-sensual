// Command to check time and memory usage:
/usr/bin/time -v ./tmp
// See "Maximum resident set size" for max memory used
// Commands for interactive checker:
mkfifo fifo
(./solution < fifo) | (./interactor > fifo)
// Does not work on the Windows file system, i.e., /mnt/c/
// The special fifo file must be used, otherwise the
// solution will not wait for input and will read EOF