# Carrito Bluetooth

Carrito de 4 motores controlado desde el celular por Bluetooth.

**Página con el esquemático y el proceso:** https://geobaas.github.io/carrito-bluetooth/

## Componentes

- Arduino Uno
- Driver de motores L298N
- Módulo Bluetooth HC-05
- 4 motores DC con chasis
- Batería de 7 a 12 V
- App Android: *Arduino Bluetooth RC Car*

## Conexiones

| L298N | Arduino | Función |
|-------|---------|---------|
| ENA | D5 | Velocidad izquierda (PWM) |
| IN1 | D7 | Dirección izquierda |
| IN2 | D8 | Dirección izquierda |
| IN3 | D9 | Dirección derecha |
| IN4 | D10 | Dirección derecha |
| ENB | D6 | Velocidad derecha (PWM) |
| 5V | 5V | Alimenta al Arduino |
| GND | GND | Tierra común |

| HC-05 | Arduino |
|-------|---------|
| VCC | 5V |
| GND | GND |
| TXD | D2 |
| RXD | D3 (opcional, con divisor 1k/2k) |

La batería va al borne de 12 V y GND del L298N. Los dos motores de cada lado van en paralelo (OUT1/OUT2 izquierda, OUT3/OUT4 derecha).

## Comandos

| Letra | Acción |
|-------|--------|
| F / B | Adelante / atrás |
| L / R | Girar izquierda / derecha |
| G / I | Adelante-izquierda / adelante-derecha |
| H / J | Atrás-izquierda / atrás-derecha |
| S | Alto |
| 0–9 | Velocidad |
| q | Velocidad máxima |

Si un lado gira al revés, cambia `INVERTIR_IZQ` o `INVERTIR_DER` a `true` en [carrito_bluetooth.ino](carrito_bluetooth.ino).
