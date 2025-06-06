# ✨ Smart Text Editor – Data Structures Project

A console-based intelligent text editor built using C++. This project demonstrates real-world usage of core **Data Structures** concepts, offering features like **auto-suggestions using Trie Trees**, **text compression using Huffman Encoding**, and **persistent file storage for history**.

---

## 📚 Key Data Structures Used

| Concept | Usage |
|--------|-------|
| **Trie Tree** | Real-time auto-complete and word suggestion |
| **Huffman Tree** | Efficient text compression and decompression |
| **Heap / Priority Queue** | Used internally for Huffman encoding |
| **File I/O** | Load and save documents with history |
| **Stacks/Queues** | Undo/Redo (optional extension or future work) |

---

## 🚀 Features

### 🔤 Auto-Suggestion using Trie
- Suggests possible word completions as the user types.
- Supports dynamic insertion of words into the dictionary.
- Based on character-by-character traversal of a Trie data structure.

### 📦 Huffman Encoding (Compression)
- Compresses entered text using frequency-based encoding.
- Reduces file size when saving documents.
- Encodes characters based on shortest prefix-free binary codes.

### 🔓 Huffman Decoding (Decompression)
- Decompresses encoded files back to original content.
- Ensures data is accurately reconstructed from compressed format.

### 💾 Save & Load Files
- Saves current session/document into a file.
- Loads previous sessions or compressed documents.
- Keeps history to allow recovery of previous data.

---

## 🔧 How It Works

### Trie for Suggestions:
- Every character typed is matched against a dictionary trie.
- Suggestions are returned from the TrieNode subtree based on current prefix.
- Efficient O(k) time complexity where `k` is the length of the prefix.

### Huffman Encoding:
- Frequency of each character is calculated.
- A Min Heap (Priority Queue) is used to build Huffman Tree.
- Generates optimal binary codes for each character.
- Encoded data is written to a file for compression.

### File Handling:
- Supports both plain text and encoded file formats.
- Automatically recognizes file type and decodes if needed.

---

## 🧠 Learning Outcomes

This project solidifies understanding of:
- Recursive tree traversal (for both Trie and Huffman Tree)
- Efficient data encoding and compression
- Using heaps for greedy algorithms
- File reading/writing and stream manipulation in C++
- Designing interactive, data-driven console applications

---



