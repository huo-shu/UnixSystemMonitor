#!/bin/bash
# Release script for Unix System Monitor

set -e

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

echo -e "${GREEN}Unix System Monitor Release Script${NC}"
echo "================================="

# Check if running on Linux or compatible environment (MSYS2/Cygwin)
if [[ "$OSTYPE" != "linux-gnu"* && "$OSTYPE" != "msys" && "$OSTYPE" != "cygwin" ]]; then
    echo -e "${RED}Error: This script requires Linux or compatible environment${NC}"
    echo -e "${YELLOW}Current OSTYPE: $OSTYPE${NC}"
    exit 1
fi

# Check if git is installed
if ! command -v git &> /dev/null; then
    echo -e "${RED}Error: git is not installed${NC}"
    exit 1
fi

# Check if gcc is installed
if ! command -v gcc &> /dev/null; then
    echo -e "${RED}Error: gcc is not installed${NC}"
    exit 1
fi

# Use gcc directly if make is not available
if ! command -v make &> /dev/null; then
    echo -e "${YELLOW}Warning: make is not installed, using gcc directly${NC}"
    USE_GCC_DIRECTLY=true
else
    USE_GCC_DIRECTLY=false
fi

# Get version from user
read -p "Enter version number (e.g., 1.0.0): " VERSION

if [[ ! $VERSION =~ ^[0-9]+\.[0-9]+\.[0-9]+$ ]]; then
    echo -e "${RED}Error: Invalid version format. Use semantic versioning (e.g., 1.0.0)${NC}"
    exit 1
fi

TAG_NAME="v$VERSION"

# Check if tag already exists
if git rev-parse "$TAG_NAME" >/dev/null 2>&1; then
    echo -e "${RED}Error: Tag $TAG_NAME already exists${NC}"
    exit 1
fi

echo -e "${YELLOW}Building project...${NC}"
if [ "$USE_GCC_DIRECTLY" = true ]; then
    # Use gcc directly
    rm -f monitor.o monitor
    gcc -Wall -Wextra -std=c99 -c src/main.c -o monitor.o
    gcc -Wall -Wextra -std=c99 src/main.c -o monitor
else
    # Use make
    make clean
    make all
fi

# Verify build was successful
if [ ! -f "monitor.o" ] || [ ! -f "monitor" ]; then
    echo -e "${RED}Error: Build failed${NC}"
    exit 1
fi

echo -e "${GREEN}Build successful!${NC}"

echo -e "${YELLOW}Creating git tag...${NC}"
git add .
git commit -m "Release $TAG_NAME" || true
git tag -a "$TAG_NAME" -m "Release version $VERSION"

echo -e "${GREEN}Tag $TAG_NAME created successfully!${NC}"

echo -e "${YELLOW}To publish the release:${NC}"
echo "1. Push the tag: git push origin $TAG_NAME"
echo "2. The GitHub Actions workflow will automatically build and create the release"
echo "3. Check the Releases page on GitHub for your published files"

echo -e "${GREEN}Release process initiated!${NC}"