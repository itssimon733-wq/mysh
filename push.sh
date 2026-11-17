
#!/bin/bash

EXECUTABLE="mysh"
COMMIT_MSG="${1:-Updated C++ shell}"

echo "========================================="
echo "🚀 Building and pushing mysh..."
echo "========================================="

# Discover all C++ source files
mapfile -t CPP_FILES < <(find src -name "*.cpp" -type f)

if [ ${#CPP_FILES[@]} -eq 0 ]; then
    echo "⚠️ No C++ source files found!"
    exit 1
fi

# Compile the project
echo "🔨 Compiling..."

if ! g++ -std=c++17 -Wall -Wextra -Iinclude \
    "${CPP_FILES[@]}" -o "$EXECUTABLE"; then
    echo "⚠️ Compilation failed!"
    exit 1
fi

echo "🎉 Compilation successful!"

# Stage and commit
echo "📦 Staging changes..."
git add -A

echo "📝 Creating commit..."

if ! git commit -m "$COMMIT_MSG"; then
    echo "⚠️ Commit failed or nothing to commit."
    exit 1
fi

# Push to GitHub and GitLab
echo "🌐 Pushing to GitHub and GitLab..."

if git push origin main; then
    echo "🎉 Successfully pushed!"
else
    echo "⚠️ Push failed. Check your remote configuration."
    exit 1
fi
