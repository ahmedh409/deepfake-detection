# Peregrine: Decentralized Deepfake Detection & Media Provenance

A research prototype for verifying the authenticity of digital media using **perceptual hashing, distributed ledgers, and peer-to-peer verification**.

The project originated at the University of Virginia as an alternative to treating deepfake detection purely as an image-classification problem. Instead of relying exclusively on a machine-learning model to decide whether pixels "look fake," Peregrine explores whether trusted media can be authenticated through **provenance**: generating robust signatures for legitimate media and preserving those signatures in a distributed, tamper-resistant record.

The original concept won **1st place in the 2021 iDISPLA University Adversarial AI/ML Challenge.

## Motivation

Deepfake-generation methods improve rapidly. A detector trained against today's manipulation techniques can therefore become less effective against tomorrow's -- but can we verify where media came from rather than relying only on detecting how it was manipulated?

The proposed architecture combines:

1. Trusted media publishers
2. Perceptual media hashing
3. Cryptographic hashing
4. A distributed ledger
5. Peer-to-peer verification
6. ML detection where provenance alone is insufficient

The goal is not to eliminate ML, but to reduce the burden placed on a single centralized deepfake-classification model.

## Concept

A simplified workflow looks like this:

```text
        Trusted Publisher
               │
               ▼
        Original Media
               │
               ▼
      Perceptual Hashing
               │
               ▼
      Cryptographic Record
               │
               ▼
       Distributed Ledger
        /      |       \
       /       |        \
    Node A   Node B    Node C
       \       |        /
        \      |       /
          Verification
               │
               ▼
        Media Consumer
```

When trusted media is published, the system generates a signature representing that media. The signature can then be stored in a ledger shared across participating nodes. When a user later encounters a piece of media, its signature can be compared against trusted records to help determine whether it corresponds to authenticated content or may have been altered. Perceptual hashing is useful because ordinary cryptographic hashes change completely when even one bit changes. Media, however, is routinely resized, compressed, transcoded, or otherwise modified without changing its semantic content.

## What This Repository Implements

This repository contains prototype implementations of several pieces of that architecture.

### Blockchain / ledger

C++ data structures for maintaining a blockchain-like record of media information. The prototype includes cryptographic hashing and early proof-of-work experimentation used to explore immutable record storage.

### Perceptual hashing

Prototype image-hashing functionality for creating signatures that remain useful when comparing transformed media.

### Distributed nodes

Nodes are modeled as independent processes participating in the network. Development work in this repository includes:

* unique node identities and network information
* independent node processes
* local blockchain construction
* blockchain export and verification
* node simulation
* peer discovery / node lists

### Peer-to-peer communication

Networking functionality was developed around TCP sockets and Boost.Asio. The prototype progressed to a state in which participating nodes could:

* run their own TCP server
* establish connections with other nodes
* maintain multiple peer sockets
* send data to other nodes
* receive data from other nodes

## Repository Structure

```text
deepfake-detection/
├── blockchain/        # blockchain / ledger implementation
├── hashing/           # perceptual and cryptographic hashing work
├── node/              # distributed-node and networking logic
├── perceptographic/   # external perceptual-hashing dependency/submodule
├── tests/             # system and component tests
├── Makefile
└── testing-harness.cpp
```

## Building

This is an older research prototype, not a maintained production security package. Modern compilers and library versions may require minor changes.

Clone the repository and its submodules:

```bash
git clone --recurse-submodules https://github.com/ahmedh409/deepfake-detection.git
cd deepfake-detection
```

The project includes a `Makefile` for building the prototype:

```bash
make
```

See the source tree and Makefile for the currently available test and simulation targets.

## Project History

### 2021 — iDISPLA Challenge

The original deepfake-provenance concept was developed by Ahmed Hussain, then an undergraduate computer-engineering student at the University of Virginia. The project won first place in the national iDISPLA University Adversarial AI/ML Challenge.

### 2021–2022 — Prototype Development

After the initial competition proposal, implementation work expanded as aforementioned.

## Recognition & Media

### University of Virginia

* [UVA Engineering — UVA Undergrads Offer New Approach to Detecting Deepfakes](https://engineering.virginia.edu/news-events/news/uva-undergrads-offer-new-approach-detecting-deepfakes)
* [UVA Today — UVA Undergrads Offer New Approach to Detecting 'Deepfake' Videos](https://news.virginia.edu/content/uva-undergrads-offer-new-approach-detecting-deepfake-videos)

### Radio

* [WVTF / Radio IQ — Fact or Fiction: Two UVA Students Tackle Deepfakes](https://www.wvtf.org/news/2021-06-18/fact-or-fiction-two-uva-students-tackle-deepfakes)

### TV Appearance

* [29News / WVIR — UVA students working on deepfake detection technology](https://www.29news.com/2021/06/16/uva-students-working-deepfake-detection-technology/)

### Investigative Coverage

* [InvestigateTV — Swapped Out: Hackers target social media users with high-tech fake videos](https://www.investigatetv.com/2022/05/16/swapped-out-hackers-target-social-media-users-with-high-tech-fake-videos/)

## Status

This repository should be treated as a research and engineering prototype.

It is useful for exploring decentralized media provenance, perceptual hashing, distributed verification, blockchain-style ledgers, and peer-to-peer networking. It is not production-ready deepfake-detection or cybersecurity software and should not be relied upon as an authoritative media-authentication service.

## Authors & Acknowledgments

The original competition concept was developed by Ahmed Hussain and Zachary Yahn at the University of Virginia with the support of Prof. Mircea Stan and Dr. Samiran Ganguly. Subsequent implementation work involved additional significant contributions from Samuel Buxbaum and additional contributors; see this repository's commit history for individual contributions.

## License

This repository is released under the **GNU General Public License v3.0**.

See [`LICENSE.md`](LICENSE.md) for details.
