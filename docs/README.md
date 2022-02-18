# diary

## v1.0
1. encryption
 1.1 for each file your password
 1.2 (password as encryption, decryption key) / (file access password)?

2. read / write to 1 file
 2.1 (contents at the beginning of the file) / (at the end of the file) / (scattered through the file (after each section is header with info about the next section))
 2.2 for the content as a whole is required
 ����- yes, time
  2.2.1 required for scattered content
  ����- the number of bytes occupying the next section
�  ���-Long entry to the calendar (will have to walk around the file) though
  2.2.2 for content at the beginning of the file -
��  ��- leave memory for all content (trabla, xz how much to allocate, memory may run out)
  2.2.3 for end-of-file content
��  ��-move all content every time
���  �-address at the beginning of each section
���  �- the number of bytes for this section
���  �+ quick calendar entry
���  �- Long file entry if content is large

3. calendar

4. Guys?

## v2.0
### first lane e.g.
_date.time_size_
_2022/2/18.19:50_000030_

### create file
check if file is empty(error if no)
move to unicode?
write first line with password size 0

### open file
check if file is not empty % check if content of file bigger than first lane
check first line and try password on it(password is invalid)
check all file if it is correct, show error if not(file is corrupted)
show treeview with history

### write to file
check if file password is correct
check all file if it is correct, show error if not(file is corrupted)
go to end file and write new text

### read from file
if user push on date in treeview
print data from this date
