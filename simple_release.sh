#!/bin/bash
# Simple Release script for Unix System Monitor
# This script only creates git tags, compilation should be done on Linux via GitHub Actions

set -e

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

echo -e "${GREEN}Unix System Monitor Simple Release Script${NC}"
echo "============================================"
echo -e "${YELLOW}Note: This script only creates git tags.${NC}"
echo -e "${YELLOW}Compilation will be done automatically by GitHub Actions on Linux.${NC}"
echo ""

# Check if git is installed
if ! command -v git &> /dev/null; then
    echo -e "${RED}Error: git is not installed${NC}"
    exit 1
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

echo -e "${YELLOW}Creating git tag...${NC}"

# Add all files to git
git add .

# Try to commit, but don't fail if there are no changes
git commit -m "Release $TAG_NAME" || echo -e "${YELLOW}No changes to commit, continuing...${NC}"

# Create the tag
git tag -a "$TAG_NAME" -m "Release version $VERSION"

echo -e "${GREEN}Tag $TAG_NAME created successfully!${NC}"
echo ""
echo -e "${YELLOW}Next steps:${NC}"
echo "1. Push the tag: git push origin $TAG_NAME"
echo "2. GitHub Actions will automatically build on Linux and create the release"
echo "3. Check the Releases page on GitHub for your compiled files"
echo ""
echo -e "${GREEN}Release process initiated!${NC}"