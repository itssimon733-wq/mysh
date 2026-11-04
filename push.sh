#!/bin/bash
CPP_FILE="main.cpp"
EXECUTABLE="main"
COMMIT_MSG="${1:-Updated C++ shell file}"

echo "========================================="
echo "🚀 Starting C++ Compilation & Git Push..."
echo "========================================="

if [ -f "$CPP_FILE" ]; then
    echo "Compiling $CPP_FILE..."
    g++ "$CPP_FILE" -o "$EXECUTABLE"

    if [ $? -ne 0 ]; then
        echo "❌ Compilation failed! Fix your code dummy🙂‍↔️"
        exit 1
    fi
    echo "✔️ Compilation successful!"
    else
        echo "⚠️ Warning $CPP_FILE not found, skipping compilation."
    fi

    echo "📦 Staging changes..."
    git add .

    echo "📝 Commiting with message: '$COMMIT_MSG'..."
    git commit -m "$COMMIT_MSG"

    echo "🌐 Pushing simultaneously to GitHub and GitLab..."
    git push origin main

    if [ $? -eq 0 ]; then
        echo "🎉 Successfully pushed to both GitHub and GitLab!"
    else
        echo "❌ Push failed. Check your network or remote configuration."
    fi