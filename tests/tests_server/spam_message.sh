#!/bin/bash
# Script d'envoi de plusieurs messages à une connexion ouverte

# Ouvrir la connexion
nc -w 0 20.216.184.69 4242 >/dev/null 2>&1 &

# Envoyer plusieurs messages à la suite
for i in {1..100000}
do
  echo $(tr -dc '[:print:]' </dev/urandom | head -c 10000)| nc -w 0 20.216.184.69 4242 >/dev/null 2>&1 &
done

# Attendre que tous les messages soient envoyés
wait

echo "Tous les messages ont été envoyés"
