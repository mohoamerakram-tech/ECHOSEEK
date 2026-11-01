# Validation Notes

## Scope

The ECHOSEEK evaluation was performed in an isolated lab using a Windows 11 x64 virtual machine and a separate Linux system for controlled research infrastructure. Testing was limited to systems and accounts authorized for the internship project.

The public repository records outcomes and one small original helper without publishing the complete implementation, test artifact, infrastructure, or procedure needed to reproduce offensive behavior.

## Evidence chain

The private project archive contains:

1. the original source and reproducible build materials;
2. the resulting test binary and file metadata;
3. endpoint-security screenshots captured before, during, and after execution;
4. runtime process and memory observations;
5. controlled server-side session evidence;
6. a 57-page engineering report connecting the design, method, observations, and limitations;
7. signed internship completion and evaluation documents.

The public release includes three low-risk screenshots and a sanitized test video. The video retains the Defender and runtime observations, but audio, infrastructure views, session metadata, and transfer logs are excluded. Stronger evidence is withheld because it contains infrastructure identifiers, personal data, or operational details.

## Reported observations

| Product / layer | Observation in the documented configuration |
|---|---|
| Microsoft Defender | The captured custom scan reported no threats, and the Windows Security dashboard showed no action required after the documented run. |
| Malwarebytes | No alert was recorded in the tested real-time and heuristic configuration. |
| Bitdefender static and memory-oriented checks | No alert was recorded in the tested configuration. |
| Bitdefender advanced behavioral protection | Runtime behavior was detected. This is the principal documented limitation of the prototype. |

## Interpretation limits

- These results describe one controlled environment and one period in 2026.
- Security products, signatures, cloud models, and behavioral rules change continuously.
- A screenshot shows the state captured at that moment; it does not prove a universal or durable capability.
- The results should not be interpreted as a current benchmark, a guarantee, or guidance for bypassing a security product.
- The behavioral detection is reported because negative results are essential to credible security research.

## Private verification

For legitimate academic or recruitment review, additional evidence may be shown privately with infrastructure identifiers, personal data, signatures, and operational details redacted as appropriate. Beyond the clearly identified public excerpt, no private source, binary, test artifact, or deployment procedure will be distributed.
