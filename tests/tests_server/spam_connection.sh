#!/bin/bash
# Script d'ouverture de connexions simultanées sur l'adresse IP 127.0.0.1 et le port 4242 sans attendre de réponse

# Définir le nombre de connexions à ouvrir
NUM_CONNEXIONS=100000

# Boucle pour ouvrir les connexions
for ((i=1; i<=NUM_CONNEXIONS; i++))
do
  # Ouvrir une nouvelle connexion en arrière-plan sans attendre de réponse
  nc -w 0 20.216.184.69 4242 >/dev/null 2>&1 &
done

echo "Toutes les connexions ont été ouvertes"
