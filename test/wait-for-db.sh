#!/bin/sh
until pg_isready -h db -U testuser -d testdb; do
  echo "Waiting for PostgreSQL..."
  sleep 1
done
