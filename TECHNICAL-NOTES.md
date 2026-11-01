# Technical Notes: Seven-Layer Evaluation Model

## Purpose

ECHOSEEK was structured as a layered endpoint-visibility experiment. Each layer represents a different class of signal available to an antivirus or endpoint detection and response product.

This document describes the research questions and observations without publishing the implementation needed to reproduce the execution chain.

## Layer model

| Layer | Research question | Signals considered | Documented observation | Public boundary |
|---:|---|---|---|---|
| 1. Static artifact analysis | What can be inferred before execution? | File signatures, recognizable byte patterns, literal strings, import surface, PE structure, and entropy | The captured Microsoft Defender custom scan reported no threat | Public code contains read-only PE and entropy analysis only |
| 2. Reputation and heuristics | Does the artifact resemble known or suspicious software? | Metadata coherence, file history, cloud reputation, unusual imports, and structural anomalies | No alert was recorded in the documented default Windows 11 configuration | Metadata values and private build decisions are withheld |
| 3. Environment and sandbox analysis | Does execution differ inside a short-lived or synthetic environment? | Timing behavior, resource profile, interaction state, and environmental consistency | The controlled run reached its intended runtime phase | Thresholds, checks, and decision logic are withheld |
| 4. Telemetry and API observation | Which user-mode events expose the execution chain? | Event telemetry, API call visibility, module observation, and security-product hooks | User-mode visibility was reduced in the tested configuration | No telemetry-modification code or patch location is public |
| 5. Native-call interception | What remains visible when conventional API paths are not used? | User-to-kernel transition, service selection, call origin, and return address | The intended native operations completed in the lab | Resolution algorithms, stubs, identifiers, and call sequences are withheld |
| 6. Memory-region inspection | How do page type and protection history affect detection? | Private versus mapped regions, writable/executable transitions, image markers, and scan timing | The tested static and memory-oriented checks did not identify the staged content | Allocation, mapping, transformation, and dispatch code are withheld |
| 7. Behavioral correlation | Can the product correlate the complete runtime story? | Call-stack provenance, saved instruction pointers, thread lineage, process context, and network behavior | Bitdefender Advanced Threat Defense detected the runtime behavior | No corrective bypass or next-stage implementation is published |

## Core finding

The project separated two defensive viewpoints:

1. **Spatial visibility**: what is present in the file, import table, process modules, and memory map.
2. **Temporal visibility**: how execution arrived at a sensitive operation, including call-stack and event history.

The prototype reduced several spatial signals in the documented lab, but the advanced behavioral layer reconstructed enough temporal context to detect the activity. This was the most important negative result in the evaluation.

## Why implementation details are withheld

The private components are individually understandable systems-programming exercises, but their composition creates an operational loader. Publishing exact call sequences, byte patterns, patch points, configuration handling, memory transitions, or dispatch logic would turn a portfolio record into a reusable implementation.

The public release therefore exposes:

- the complete layer model;
- the defensive signals examined;
- outcome and limitation reporting;
- compile-ready analytical C++;
- sanitized evidence.

It does not expose the mechanism that changes those signals.

## Evidence mapping

| Evidence | Layers supported |
|---|---|
| Defender custom-scan capture | 1 and 2 |
| Runtime process and memory observation | 3 and 6 |
| Controlled-session segment | 4, 5, and 6 at an outcome level only |
| Bitdefender behavioral result | 7 |
| Private report and source archive | All layers; available only for legitimate private review |
