# Social Media Platform in C

## Overview
This project implements a simple **command-line based social media platform** in C.  
It allows users to create posts, add comments and replies, delete them, and navigate between posts.  
The system demonstrates the use of **linked lists**, modular programming, and structured data handling in C.

---

## Features
- Add a Post
- Add a Comment to a Post
- Add a Reply to a Comment
- Delete a Comment
- Delete a Reply
- View all Posts, Comments, and Replies
- Navigate to Current, Next, and Previous Post
- Proper error handling for invalid inputs

---

## Folder Structure
```
rollnumber/
│
├── code/
│   ├── main.c
│   ├── platform.c
│   ├── platform.h
│   ├── post.c
│   ├── post.h
│   ├── comment.c
│   ├── comment.h
│   ├── reply.c
│   ├── reply.h
│   ├── Makefile
│   └── README.md
│
└── Git.docx
```

---

## Compilation Instructions

### Using Makefile
```bash
make
./platform
```

### Manual Compilation
```bash
gcc main.c platform.c post.c comment.c reply.c -o platform
./platform
```

---

## Function Summary

| Function | Description |
|-----------|-------------|
| `addpost` | Adds a new post |
| `addcomment` | Adds a comment to a post |
| `addreply` | Adds a reply to a comment |
| `deletecomment` | Deletes a comment from a post |
| `deletereply` | Deletes a reply from a comment |
| `displayplatform` | Displays all posts, comments, and replies |
| `viewcomments` | Displays comments of a specific post |
| `currpost` | Displays the current post |
| `nextpost` | Displays the next post |
| `previouspost` | Displays the previous post |
| `freeposts` | Frees all posts and related data |
| `freecomments` | Frees all comments for a post |
| `freereplies` | Frees all replies for a comment |

---

## Data Structures

### Post
```c
struct post {
    char username[50];
    char caption[200];
    struct comment* comments;
    struct post* next;
    struct post* prev;
};
```

### Comment
```c
struct comment {
    char username[50];
    char content[200];
    struct reply* replies;
    struct comment* next;
    struct comment* prev;
};
```

### Reply
```c
struct reply {
    char username[50];
    char content[200];
    struct reply* next;
    struct reply* prev;
};
```

---

## Sample Output
```
========= SOCIAL MEDIA PLATFORM =========
1. Add Post
2. Add Comment
3. Add Reply
4. Delete Comment
5. Delete Reply
6. View Platform
7. Current Post
8. Next Post
9. Previous Post
10. View Comments of a Post
11. Exit
=========================================
Enter your choice: 1
Enter username: Bharath
Enter caption: Hello World
✅ Post added successfully!
```

Error handling examples:
```
Next post does not exist.
Post not found.
No comments available.
```

---

## Assumptions
- Indices for posts, comments, and replies start from **1**.
- Input lengths are within defined buffer limits.
- Data is stored in memory only (no file storage).
- All allocated memory is freed before program termination.

---

## Bonus
The reply functionality is implemented as a **bonus feature**.  
It does not add extra marks but may help compensate for partial deductions elsewhere.

---

## Git Link
Refer to `Git.docx` for the Git repository link.

---

## Author
**Bharath Kumar Reddy Gopireddy**
