# monero-c
[![Build](https://github.com/everoddandeven/monero-c/actions/workflows/build.yml/badge.svg)](https://github.com/everoddandeven/monero-c/actions/workflows/build.yml)

A C API for creating Monero applications using a bridge to [monero v0.18.5.0 'Fluorine Fermi'](https://github.com/monero-project/monero/tree/v0.18.5.0).

* Supports client-side wallets using C API.
* Supports multisig, view-only, and offline wallets.
* Wallet types are interchangeable by conforming to a [common interface](https://woodser.github.io/monero-java/javadocs/monero/wallet/MoneroWallet.html).
* Uses a clearly defined [data model and API specification](https://woodser.github.io/monero-java/monero-spec.pdf) intended to be intuitive and robust.
* Query wallet transactions, transfers, and outputs by their properties.
* Receive notifications when wallets sync, send, or receive.

## Architecture

<p align="center">
	<img width="85%" height="auto" src="docs/architecture.png"/><br>
	<i>Build C
     applications using C API bindings to <a href="https://github.com/monero-project/monero">monero-project/monero</a>.  Wallet implementations are interchangeable by conforming to a common interface, <a href="https://woodser.github.io/monero-java/javadocs/monero/wallet/MoneroWallet.html">MoneroWallet</a>.</i>
</p>

## Related projects

* [monero-cpp](https://github.com/woodser/monero-cpp)
* [monero-java](https://github.com/woodser/monero-cpp)
* [monero-ts](https://github.com/woodser/monero-ts)
* [monero-python](https://github.com/everoddandeven/monero-python)

## License

This project is licensed under MIT.
